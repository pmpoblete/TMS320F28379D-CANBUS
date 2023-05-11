//###########################################################################
//
// FILE:   controllers.h
//
// TITLE:  Control functions for a three-phase CHB with 3 SMs
//
//! Developed by:
//! Pablo Poblete
//! University of Technology Sydney, Australia
//! pmpoblete@ieee.org
//!
//! October 2022
//!
//
//###########################################################################



//----------------------------------------------------------------
// Linear Transformations
//----------------------------------------------------------------

/*
 * function:  abc2alpha_beta
 * --------------------
 * Description: this function performs the constant
 * amplitud abc to alpha beta transform
 *
 * inputs______
 * 1) pointer with the system states. Currents are included in that structure
 *
 * outputs_____
 * 1) struct alpha_beta_v: structure with alpha beta variables
 */
struct alpha_beta_v abc2alpha_beta(float xa, float xb, float xc)
{
    struct alpha_beta_v v;
    v.alpha = 0.6667 * (xa - 0.5 * xb - 0.5 * xc);
    v.beta = 0.6667 * (0.8660 * xb - 0.8660 * xc);

    return v;
}



/*
 * function:  alpha_beta2abc
 * --------------------
 * Description: this function performs the constant
 * amplitud abc to alpha beta transform
 *
 * inputs______
 * 1) pointer with the system states. Currents are included in that structure
 *
 * outputs_____
 */
struct abc_v alpha_beta2abc(float xalpha, float xbeta, float x0)
{
    struct abc_v v;
    v.a = 0.707106781 * x0 + xalpha;
    v.b = 0.707106781 * x0 - 0.5 * xalpha + 0.866025404 * xbeta;
    v.c = 0.707106781 * x0 - 0.5 * xalpha - 0.866025404 * xbeta;

    return v;
}



/*
 * function:  alpha_beta2dq
 * --------------------
 * Description: this function performs the constant
 * amplitud alpha-beta to dq frame
 *
 * inputs______
 * 1) alpha
 * 2) beta
 * 3) wt
 *
 * outputs_____
 * 1) struct alpha_beta_v: structure with alpha beta variables
 */
struct dq_v alpha_beta2dq(float xalpha, float xbeta, float wt)
{
    struct dq_v v;

    float cosWT = cosf(wt);
    float sinWT = sinf(wt);

    v.d = xalpha*sinWT - xbeta*cosWT;
    v.q = xalpha*cosWT + xbeta*sinWT;

    return v;
}



/*
 * function:  dq2alpha_beta
 * --------------------
 * Description: this function performs the constant
 * amplitud alpha-beta to dq frame
 *
 * inputs______
 * 1) d
 * 2) q
 * 3) wt
 *
 * outputs_____
 * 1) struct alpha_beta_v: structure with alpha beta variables
 */
struct alpha_beta_v dq2alpha_beta(float xd, float xq, float wt)
{
    struct alpha_beta_v v;

    float cosWT = cosf(wt);
    float sinWT = sinf(wt);

    v.alpha = xd*sinWT + xq*cosWT;
    v.beta = -xd*cosWT + xq*sinWT;

    return v;
}




/*
 * function:  mag_alpha_beta
 * --------------------
 * Description: this function computes the amplitude of
 * alpha-beta signals. Can be used to determine modulating index
 *
 * inputs______
 * 1) alpha
 * 2) beta
 *
 * outputs_____
 * 1) amp: amplitude value
 */
float mag_alpha_beta(float alpha, float beta)
{
    float mag;

    mag = sqrtf(alpha*alpha + beta*beta);

    return mag;
}





/*
 * function:  PS_PWMva_RotMatrix
 * --------------------
 * Description: feedforward compensation for alpha-beta duty-cycles for a given
 * PS-PWM angle with respect to carrier 1. The calculation of the duty-cycles
 * for each SM is computed at the same time at fc, whenever the carrier 1
 * hits one of its edges
 *
 * inputs______
 * 1) *alpha_beta_v: structure with the original alpha-beta voltages before rotation
 * 2) w_zero: current frequency 2*pi*f0
 * 3) ref_angle: phase shift angle in degrees
 * 4) tc: carrier period = 1/fc
 *
 * outputs_____
 * 1) new_ab_v: structure with the rotated alpha-beta vector
 *
 */
struct alpha_beta_v PS_PWMva_RotMatrix(struct alpha_beta_v *v_ab,
                     float w_zero,
                     float ref_angle,
                     float tc,
                     float test1)
{
    struct alpha_beta_v new_ab_v;

    float time_step = ref_angle*0.00277777777778*0.5*tc;         // 0.0027778 = 1/360
    float arg = test1*w_zero*time_step;                          // test1 = -1
    float cosWT = cosf(arg);
    float sinWT = sinf(arg);

    new_ab_v.alpha = v_ab->alpha*cosWT - v_ab->beta*sinWT;
    new_ab_v.beta =  v_ab->alpha*sinWT + v_ab->beta*cosWT;


    return new_ab_v;
}



//----------------------------------------------------------------
// Control Functions
//----------------------------------------------------------------

/*
 * function:  sensor_offset_comp
 * --------------------
 * Description: compensate the adc sensor offset when enable is off
 *
 * inputs______
 * 1) duties: structure with the converter duty-cycles
 * 2) duty: desired duty-cycle for the arm [-1, 1]
 *
 * outputs_____
 *
 */
void sensor_offset_comp(struct sensor *sensor, float measurement, unsigned int EN, float alpha)
{
    if (EN == 0)
    {
        // low pass filter for offset
        sensor->ADC_reading_filter = measurement*(1-alpha) + sensor->ADC_reading_filter*alpha;
        // compute new offset
        sensor->offset += sensor->ADC_reading_filter;
    }
}



/*
 * function:  PRcontrol_step
 * --------------------
 * Description: this function computes the calculation of
 * a given PR controller
 *
 * inputs______
 * 1) PRcontroller: structure with the converter duty-cycles
 * 2) e: error signal
 *
 * outputs_____
 * u_k: control action
 */
void PRcontrol_step(struct PRcontroller *PRcontroller, float ix_r, float ix)
{
    float u_k;

    // compute error
    float e = ix_r - ix;

    // control action
    u_k = PRcontroller->a_0 * e +
          PRcontroller->a_1 * PRcontroller->e_1 +
          PRcontroller->a_2 * PRcontroller->e_2 +
          PRcontroller->b_1 * PRcontroller->u_1 -
          PRcontroller->u_2;

    // Antiwindup
    if (u_k >= 1)
    {
        u_k = 1;
        e = 0;
        PRcontroller->e_1 = 0;
    }
    else if (u_k <= -1)
    {
        u_k = -1;
        e = 0;
        PRcontroller->e_1 = 0;
    }

    // Memory
    PRcontroller->e_2 = PRcontroller->e_1;
    PRcontroller->e_1 = e;
    PRcontroller->u_2 = PRcontroller->u_1;
    PRcontroller->u_1 = u_k;
    PRcontroller->u_k = u_k;
}




/*
 * function:  PIcontrol_step
 * --------------------
 * Description: this function computes the calculation of
 * a given PR controller
 *
 * inputs______
 * 1) PIcontroller: 
 * 2) e: error signal
 *
 * outputs_____
 * u_k: control action
 */
void PIcontrol_step(struct PIcontroller *PIcontroller, float ix_r, float ix)
{
    float u_k;

    // compute error
    float e = ix_r - ix;

    // control action
    u_k = PIcontroller->k_a*e + 
          PIcontroller->k_b*PIcontroller->e_1 + 
          PIcontroller->u_1;

    // Antiwindup
    if (u_k >= 1)
    {
        u_k = 1;
    }
    else if (u_k <= -1)
    {
        u_k = -1;
    }

    // Memory
    PIcontroller->e_1 = e;
    PIcontroller->u_1 = u_k;
    PIcontroller->u_k = u_k;
}



/*
 * function:  current_fault_detection
 * --------------------
 * Description: this function is executed every sampling instant
 * to identify hazardous conditions for the converter currents
 *
 * inputs______
 * 1) fault: previous fault flag
 * 2) ia: measured current value of phase a
 * 3) ib: measured current value of phase b
 * 4) ic: measured current value of phase c
 * 5) Imax: maximum current threshold
 *
 * outputs_____
 * 1) fault: fault flag. 1 means fault.
 *
 */
unsigned int current_fault_detection(unsigned int fault, float ia, float ib, float ic, float Imax)
{
    // check for new faults only
    if (fault == 0)
    {
        // Over Current Fault. Log: fault=1
        if (fabs(ia) > Imax)
        {
            fault = 1;
        }

        if (fabs(ib) > Imax)
        {
            fault = 1;
        }

        if (fabs(ic) > Imax)
        {
            fault = 1;
        }
    }
    return fault;
}



/*
 * function:  power_fault_detection
 * --------------------
 * Description: this function is executed every sampling instant
 * to identify hazardous conditions for the converter power. In particular
 * bidirectional power flow is not allowed
 *
 * inputs______
 * 1) fault: previous fault flag
 * 2) p_inv: converter three-phase active power
 * 3) q_inv: converter three-phase reactive power
 * 5) p_min: minimum power threshold
 *
 * outputs_____
 * 1) fault: fault flag. 2 means power fault.
 *

unsigned int power_fault_detection(unsigned int fault, float p, float q, float p_min)
{
    // check for new faults only
    if (fault == 0)
    {
        // Reverse power flow. Log: fault=2
        if (p < p_min)
        {
            fault = 2;
        }

    }
    return fault;
}
 */


/*
 * function:  check_user_EN
 * --------------------
 * Description: this function checks the value of an user
 * enable global variable to switch off the converter
 *
 * inputs______
 * 1) duties: structure with the converter duty-cycles
 * 2) EN: user enable
 *
 * outputs_____
 *
 */
void check_user_EN(struct duty_cycles *duty_cycles, unsigned int EN)
{
    if (EN == 0)
    {
        // hardware has inverse logic
        duty_cycles->EN1 = 1;
        duty_cycles->EN2 = 1;
    }
    else
    {
        duty_cycles->EN1 = 0;
        duty_cycles->EN2 = 0;
    }
}



/*
 * function:  balanced_modulation_arm_a
 * --------------------
 * Description: this function gives the same duty-cycle value to
 * each SM of the arm of phase-a
 *
 * inputs______
 * 1) duties: structure with the converter duty-cycles
 * 2) duty: desired duty-cycle for the arm [-1, 1]
 *
 * outputs_____
 *
 */

void balanced_modulation_arm_a(struct duty_cycles *duty_cycles, float duty)
{
    // SM 1:
    duty_cycles->d1_sm1_a = 0.5 * duty + 0.5;
    duty_cycles->d2_sm1_a = -0.5 * duty + 0.5;
    // SM 2:
    duty_cycles->d1_sm2_a = 0.5 * duty + 0.5;
    duty_cycles->d2_sm2_a = -0.5 * duty + 0.5;
    // SM 3:
    duty_cycles->d1_sm3_a = 0.5 * duty + 0.5;
    duty_cycles->d2_sm3_a = -0.5 * duty + 0.5;
}

void balanced_modulation_arm_b(struct duty_cycles *duty_cycles, float duty)
{
    // SM 1:
    duty_cycles->d1_sm1_b = duty ;
    duty_cycles->d2_sm1_b = -duty;
    // SM 2:
    duty_cycles->d1_sm2_b = duty;
    duty_cycles->d2_sm2_b = -duty;
    // SM 3:
    duty_cycles->d1_sm3_b = duty;
    duty_cycles->d2_sm3_b = -duty;
}

void balanced_modulation_arm_c(struct duty_cycles *duty_cycles, float duty)
{
    // SM 1:
    duty_cycles->d1_sm1_c = 0.5 * duty + 0.5;
    duty_cycles->d2_sm1_c = -0.5 * duty + 0.5;
    // SM 2:
    duty_cycles->d1_sm2_c = 0.5 * duty + 0.5;
    duty_cycles->d2_sm2_c = -0.5 * duty + 0.5;
    // SM 3:
    duty_cycles->d1_sm3_c = 0.5 * duty + 0.5;
    duty_cycles->d2_sm3_c = -0.5 * duty + 0.5;
}




/*
 * function:  modulation
 * --------------------
 * Description: this function provides modulating signals
 * for each SM
 *
 * inputs______
 * 1) duties: structure with the converter duty-cycles. Used for writing PWM register
 * 2) arm_duties: arm normalized duty cycles [-1, 1]
 * 3) arm_VDC: DC voltage available at each arm
 * 4) vdc_SMs_v: dc voltages of each SM
 * 5) ma: modulation index for each SM. This modulation index is regarding nominal modulated voltage
 *
 * outputs_____
 *
 */
void modulation_std(struct duty_cycles *duty_cycles, 
                struct abc_v *d,
                struct alpha_beta_v *d_ab,
                struct signal_x_sm *v_dc_norm, 
                struct signal_x_sm *ma_sms)
{
    float ma = mag_alpha_beta(d_ab->alpha, d_ab->beta);
    float filter = 0.9999;

    // SM-1
    ma_sms->sm1_a =  ma_sms->sm1_a*filter + (1-filter)*ma*v_dc_norm->sm1_a;   
    duty_cycles->d1_sm1_a = 0.5*d->a*v_dc_norm->sm1_a + 0.5; 
    duty_cycles->d2_sm1_a = -duty_cycles->d1_sm1_a + 1.0;

    ma_sms->sm1_b =  ma_sms->sm1_b*filter + (1-filter)*ma*v_dc_norm->sm1_b;                    
    duty_cycles->d1_sm1_b = 0.5*d->b*v_dc_norm->sm1_b + 0.5; 
    duty_cycles->d2_sm1_b = -duty_cycles->d1_sm1_b + 1.0;
    
    ma_sms->sm1_c =  ma_sms->sm1_c*filter + (1-filter)*ma*v_dc_norm->sm1_c; 
    duty_cycles->d1_sm1_c = 0.5*d->c*v_dc_norm->sm1_c + 0.5; 
    duty_cycles->d2_sm1_c = -duty_cycles->d1_sm1_c + 1.0;

    // SM-2      
    ma_sms->sm2_a =  ma_sms->sm2_a*filter + (1-filter)*ma*v_dc_norm->sm2_a;                         
    duty_cycles->d1_sm2_a = 0.5*d->a*v_dc_norm->sm2_a + 0.5; 
    duty_cycles->d2_sm2_a = -duty_cycles->d1_sm2_a + 1.0;

    ma_sms->sm2_b =  ma_sms->sm2_b*filter + (1-filter)*ma*v_dc_norm->sm2_b; 
    duty_cycles->d1_sm2_b = 0.5*d->b*v_dc_norm->sm2_b + 0.5; 
    duty_cycles->d2_sm2_b = -duty_cycles->d1_sm2_b + 1.0;

    ma_sms->sm2_c =  ma_sms->sm2_c*filter + (1-filter)*ma*v_dc_norm->sm2_c; 
    duty_cycles->d1_sm2_c = 0.5*d->c*v_dc_norm->sm2_c + 0.5; 
    duty_cycles->d2_sm2_c = -duty_cycles->d1_sm2_c + 1.0;

    // SM-3
    ma_sms->sm3_a =  ma_sms->sm3_a*filter + (1-filter)*ma*v_dc_norm->sm3_a; 
    duty_cycles->d1_sm3_a = 0.5*d->a*v_dc_norm->sm3_a + 0.5; 
    duty_cycles->d2_sm3_a = -duty_cycles->d1_sm3_a + 1.0;

    ma_sms->sm3_b =  ma_sms->sm3_b*filter + (1-filter)*ma*v_dc_norm->sm3_b; 
    duty_cycles->d1_sm3_b = 0.5*d->b*v_dc_norm->sm3_b + 0.5; 
    duty_cycles->d2_sm3_b = -duty_cycles->d1_sm3_b + 1.0;

    ma_sms->sm3_c =  ma_sms->sm3_c*filter + (1-filter)*ma*v_dc_norm->sm3_c; 
    duty_cycles->d1_sm3_c = 0.5*d->c*v_dc_norm->sm3_c + 0.5; 
    duty_cycles->d2_sm3_c = -duty_cycles->d1_sm3_c + 1.0;

}




/*
 * function:  tphase_ol_modulation
 * --------------------
 * Description: this function provides balanced three-phase
 * open loop modulation for the CHB converter
 *
 * inputs______
 * 1) duties: structure with the converter duty-cycles
 * 2) wt: angle related to current reference
 * 2) ma: modulation index [0, 1]
 *
 * outputs_____
 *

void tphase_ol_modulation(struct duty_cycles *duty_cycles, float wt, float ma)
{
    // compute arm modulating signals
    duty_cycles->da = ma * sinf(wt);
    duty_cycles->db = ma * sinf(wt - TWO_PI_THIRD);
    duty_cycles->dc = ma * sinf(wt + TWO_PI_THIRD);

    // assign arm modulating signals
    balanced_modulation_arm_a(duty_cycles, duty_cycles->da);
    balanced_modulation_arm_b(duty_cycles, duty_cycles->db);
    balanced_modulation_arm_c(duty_cycles, duty_cycles->dc);
}
 */



/*
 * function:  tphase_ol_duties
 * --------------------
 * Description: this function provides balanced three-phase
 * open loop voltages to send to the modulator
 *
 * inputs______
 * 1) duties: structure with the converter duty-cycles
 * 2) wt: angle related to current reference
 * 2) ma: modulation index [0, 1]
 *
 * outputs_____
 *
 */
struct abc_v tphase_ol_duties(float wt, float ma)
{
    struct abc_v v0;
    // compute arm modulating signals
    v0.a = ma * sinf(wt);
    v0.b = ma * sinf(wt - TWO_PI_THIRD);
    v0.c = -v0.a - v0.b;

    return v0;
}



/*
 * function:  vdc_nom_init
 * --------------------
 * Description: computes the nominal dc voltage per SM
 * for each phase
 *
 * inputs______
 * 1) duties: structure with the converter duty-cycles
 * 2) wt: angle related to current reference
 * 2) ma: modulation index [0, 1]
 *
 * outputs_____
 * 1) v_dc_nom: structure with nominal voltages per SM per phase
 */
struct abc_v vdc_nom_init(struct abc_v *arm_VDC, 
                        struct vdc_SMs_v *vdc_SMs)
{
    struct abc_v vdc_nom;
    vdc_nom.a = vdc_SMs->n_cells_inv * arm_VDC->a;   
    vdc_nom.b = vdc_SMs->n_cells_inv * arm_VDC->b;    
    vdc_nom.c = vdc_SMs->n_cells_inv * arm_VDC->c;    

    return vdc_nom;
}



/*
 * function:  update_norm_vdc
 * --------------------
 * Description: computes the normalized dc voltage of each
 * SM based on individual modulation indexes and voltage
 *
 * inputs______
 * 1) vdc_nom_sm: normalized voltage for SMs of each phase
 * 2) vdc_SMs: sm capacitor voltages
 * 2) ma: modulation index [0, 1]
 *
 * outputs_____
 * 1) v_dc_norm: structure with normalized voltages
 */
struct signal_x_sm update_norm_vdc(struct abc_v *vdc_nom_sm,
                                 struct signal_x_sm *vdc_SMs_inv, 
                                 struct signal_x_sm *ma)
{
    struct signal_x_sm v_dc_norm;
    
    v_dc_norm.sm1_a = (ma->sm1_a)*(vdc_nom_sm->a)*(vdc_SMs_inv->sm1_a);
    v_dc_norm.sm2_a = (ma->sm2_a)*(vdc_nom_sm->a)*(vdc_SMs_inv->sm2_a);
    v_dc_norm.sm3_a = (ma->sm3_a)*(vdc_nom_sm->a)*(vdc_SMs_inv->sm3_a);

    v_dc_norm.sm1_b = (ma->sm1_b)*(vdc_nom_sm->b)*(vdc_SMs_inv->sm1_b);
    v_dc_norm.sm2_b = (ma->sm2_b)*(vdc_nom_sm->b)*(vdc_SMs_inv->sm2_b);
    v_dc_norm.sm3_b = (ma->sm3_b)*(vdc_nom_sm->b)*(vdc_SMs_inv->sm3_b);

    v_dc_norm.sm1_c = (ma->sm1_c)*(vdc_nom_sm->c)*(vdc_SMs_inv->sm1_c);
    v_dc_norm.sm2_c = (ma->sm2_c)*(vdc_nom_sm->c)*(vdc_SMs_inv->sm2_c);
    v_dc_norm.sm3_c = (ma->sm3_c)*(vdc_nom_sm->c)*(vdc_SMs_inv->sm3_c);
    
   /*
    v_dc_norm.sm1_a = 1.0;
    v_dc_norm.sm2_a = 1.0;
    v_dc_norm.sm3_a = 1.0;

    v_dc_norm.sm1_b = 1.0;
    v_dc_norm.sm2_b = 1.0;
    v_dc_norm.sm3_b = 1.0;

    v_dc_norm.sm1_c = 1.0;
    v_dc_norm.sm2_c = 1.0;
    v_dc_norm.sm3_c = 1.0;
    */
    

    return v_dc_norm;
}


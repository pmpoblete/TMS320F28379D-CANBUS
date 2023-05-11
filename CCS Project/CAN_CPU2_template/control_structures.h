//###########################################################################
//
// FILE:   control_structures.h
//
// TITLE:  Definition of structures required for controllers.h
// This header need to be imported before contrllers.h
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
// Special Structure Definitions:
//----------------------------------------------------------------

/*
 * structure:  alpha_beta_v
 * --------------------
 * vector for alpha beta electrical variables
 *
 */
struct alpha_beta_v
{
    float alpha;
    float beta;
};


/*
 * structure:  dq_v
 * --------------------
 * vector for alpha beta electrical variables
 *
 */
struct dq_v
{
    float d;
    float q;
};




/*
 * structure:  abc_v
 * --------------------
 * vector for three-phase electrical variables
 *
 */
struct abc_v
{
    float a;
    float b;
    float c;
};



/*
 * structure:  sensor
 * --------------------
 * vector for alpha beta electrical variables
 *
 */
struct sensor
{
    float offset;
    float gain;
    float ADC_reading;
    float ADC_reading_filter;
};



/*
 * structure:  signal_x_sm
 * --------------------
 * contain scaling floats for each SM of the converter
 * 
 */
struct signal_x_sm
{
    // duty cycles for SMs phase-a
    float sm1_a;
    float sm2_a;
    float sm3_a;
    // duty cycles for SMs phase-b
    float sm1_b;
    float sm2_b;
    float sm3_b;
    // duty cycles for SMs phase-c
    float sm1_c;
    float sm2_c;
    float sm3_c;
};


/*
 * structure:  control_inputs
 * --------------------
 * store the info of the control inputs in different formats
 *
 */
struct control_inputs
{
    struct abc_v d_abc;         // three-phase duty-cycles [-1,1]
    struct alpha_beta_v d_ab;   // three-phase alpha-beta duty-cycles [-1, 1]
    // struct dq_v d_dq;           // three-phase dq duty-cycles [-1, 1]
    struct abc_v d_abc_ss;       // steady-state control inputs
    float  d0;                  // modulating signal for zero-seq [-1,1]
};



/*
 * structure:  duty_cycles
 * --------------------
 * store the value of the duty-cycle for each converter leg
 *
 * application example:
 * write_ePWMxB(1,duty_cycles.d1_sm1_a);
 *
 */
struct duty_cycles
{
    // duty cycles for SMs phase-a
    float d1_sm1_a;
    float d2_sm1_a;
    float d1_sm2_a;
    float d2_sm2_a;
    float d1_sm3_a;
    float d2_sm3_a;
    // duty cycles for SMs phase-b
    float d1_sm1_b;
    float d2_sm1_b;
    float d1_sm2_b;
    float d2_sm2_b;
    float d1_sm3_b;
    float d2_sm3_b;
    // duty cycles for SMs phase-c
    float d1_sm1_c;
    float d2_sm1_c;
    float d1_sm2_c;
    float d2_sm2_c;
    float d1_sm3_c;
    float d2_sm3_c;
    // duty cycles for arms
    float da;
    float db;
    float dc;
    // enables
    unsigned int EN1;
    unsigned int EN2;
};



/*
 * structure:  SM_dc_v
 * --------------------
 * store the value of dc-link voltage for each SM
 *
 */
struct vdc_SMs_v
{
    unsigned int n_cells;      
    float n_cells_inv;              // (1/n_cells) stored for efficiency        
    
    struct signal_x_sm vdc;         // capacitor voltages for each SM
    struct signal_x_sm vdc_inv;     // (1/capacitor voltage) for each SM
};



/*
 * structure:  states
 * --------------------
 * store the value of the states of the controller and important measurements
 *
 */
struct states
{
    // converter currents in abc/alpha-beta/dq frame
    struct abc_v i_abc;
    struct alpha_beta_v i_ab;
    // struct dq_v i_dq;

    // grid voltages in abc frame and alpha-beta frame
    // struct abc_v vg_abc;
    // struct alpha_beta_v vg_ab;

    // SM voltages for each phase
    struct vdc_SMs_v vdc_SMs_v;

    // converter three-phase active and reactive powers
    // float p_inv;
    // float q_inv;

    // tracking error
    float error_J;
};



/*
 * structure:  references
 * --------------------
 * store the value of the references for each state variable
 *
 */
struct references
{
    // ref current amplitud
    float I_r;
    // ref current vectors
    struct abc_v i_abc_r;
    struct alpha_beta_v i_ab_r;
    // struct dq_v i_dq_r;
};



/*
 * structure:  AnalogOutputs
 * --------------------
 * store the value of analog outputs used to debug control
 * these values need to be in pu [0,1]
 */
struct AnalogOutputs
{
    // DACs
    float analog_out1;
    float analog_out2;
};



/*
 * structure:  DigitalOutputs
 * --------------------
 * store the value of the registers for controlling
 * the digital outputs
 */
struct DigitalOutputs
{
    unsigned int EN1;
    unsigned int EN2;
    unsigned int comp_time;
    unsigned int trigger;
};



/*
 * structure:  PRcontroller
 * --------------------
 * store the value of the PR current controller important variables
 *
 */
struct PRcontroller
{
    // control action
    float u_k;

    // memory from previous actuation
    float u_1;
    float u_2;
    float e_1;
    float e_2;

    // gains
    float a_0;
    float a_1;
    float a_2;
    float b_1;
};




/*
 * structure:  PIcontroller
 * --------------------
 * store the value of the PI current controller important variables
 *
 */
struct PIcontroller
{
    // control action
    float u_k;

    // memory from previous actuation
    float u_1;
    float e_1;

    // gains
    float k_a;
    float k_b;
};



//----------------------------------------------------------------
// Initialization Functions:
//----------------------------------------------------------------

/*
 * function:  sensor_calibration
 * --------------------
 * Description: duty cycles variable initialization
 *
 * inputs______
 * 1) sensor structure: sensor structure that will be updated
 * outputs_____
 * 1) duty_0: a structure duty_cycle with all its values = 0
 *
 */
void sensor_calibration(struct sensor *sensor, float gain, float offset)
{
    sensor->gain = gain;
    sensor->offset = offset;
}



/*
 * function:  init_duties
 * --------------------
 * Description: duty cycles variable initialization
 *
 * inputs______
 *
 * outputs_____
 * 1) duty_0: a structure duty_cycle with all its values = 0
 *
 */
struct duty_cycles init_duties(void)
{
    struct duty_cycles duty_0 = {0};
    duty_0.EN1 = 0;
    duty_0.EN2 = 0;
    return duty_0;
}



/*
 * function:  init_vdc_SMs
 * --------------------
 * Description: SM capacitor voltages initialization
 *
 * inputs______
 *
 * outputs_____
 * 1) duty_0: a structure vdc_SMs_v with all its values regarding HW manual measurements
 *
 */
struct vdc_SMs_v init_vdc_SMs(void)
{
    struct vdc_SMs_v vdc_SMs_v0;

    // general definitions
    vdc_SMs_v0.n_cells = 3;
    vdc_SMs_v0.n_cells_inv = ((float) 1) /  ((float) vdc_SMs_v0.n_cells);

    // SM capacitor voltages
    // SMs phase a
    vdc_SMs_v0.vdc.sm1_a = 50;    // 50
    vdc_SMs_v0.vdc.sm2_a = 60;    // 60
    vdc_SMs_v0.vdc.sm3_a = 45;    // 45
    // SMs phase b
    vdc_SMs_v0.vdc.sm1_b = 50;
    vdc_SMs_v0.vdc.sm2_b = 50;
    vdc_SMs_v0.vdc.sm3_b = 50;
    // SMs phase c
    vdc_SMs_v0.vdc.sm1_c = 50;
    vdc_SMs_v0.vdc.sm2_c = 50;
    vdc_SMs_v0.vdc.sm3_c = 50;

    // Inverse value of SM capacitor voltages
    // phase-a
    vdc_SMs_v0.vdc_inv.sm1_a = ((float) 1) / ((float) vdc_SMs_v0.vdc.sm1_a);
    vdc_SMs_v0.vdc_inv.sm2_a = ((float) 1) / ((float) vdc_SMs_v0.vdc.sm2_a);
    vdc_SMs_v0.vdc_inv.sm3_a = ((float) 1) / ((float) vdc_SMs_v0.vdc.sm3_a);
    // phase-b
    vdc_SMs_v0.vdc_inv.sm1_b = ((float) 1) / ((float) vdc_SMs_v0.vdc.sm1_b);
    vdc_SMs_v0.vdc_inv.sm2_b = ((float) 1) / ((float) vdc_SMs_v0.vdc.sm2_b);
    vdc_SMs_v0.vdc_inv.sm3_b = ((float) 1) / ((float) vdc_SMs_v0.vdc.sm3_b);
    // phase-c
    vdc_SMs_v0.vdc_inv.sm1_c = ((float) 1) / ((float) vdc_SMs_v0.vdc.sm1_c);
    vdc_SMs_v0.vdc_inv.sm2_c = ((float) 1) / ((float) vdc_SMs_v0.vdc.sm2_c);
    vdc_SMs_v0.vdc_inv.sm3_c = ((float) 1) / ((float) vdc_SMs_v0.vdc.sm3_c);

    return vdc_SMs_v0;
}



/*
 * function:  init_arm_VDC
 * --------------------
 * Description: calculation of the arm VDC given each SM capacitor voltage value
 *
 * inputs______
 *
 * outputs_____
 * 1) arm_VDC_0: a structure abc_v with the arm maximum dc voltage
 *
 */
struct abc_v init_arm_VDC(struct signal_x_sm *vdc)
{
    struct abc_v arm_VDC_0;
    // Maximum dc voltage per arm
    arm_VDC_0.a = vdc->sm1_a + vdc->sm2_a + vdc->sm3_a;
    arm_VDC_0.b = vdc->sm1_b + vdc->sm2_b + vdc->sm3_b;
    arm_VDC_0.c = vdc->sm1_c + vdc->sm2_c + vdc->sm3_c;

    return arm_VDC_0;
}



/*
 * function:  init_modulating_index
 * --------------------
 * Description: modulating index initialization for each cell
 *
 * inputs______
 *
 * outputs_____
 * 1) modulating_index_0: a structure of modulating indexes all init in 1
 *
 */
struct signal_x_sm init_modulating_index(void)
{
    struct signal_x_sm modulating_index_0;
    // phase-a
    modulating_index_0.sm1_a = 1.0;
    modulating_index_0.sm2_a = 1.0;
    modulating_index_0.sm3_a = 1.0;
    // phase-b
    modulating_index_0.sm1_b = 1.0;
    modulating_index_0.sm2_b = 1.0;
    modulating_index_0.sm3_b = 1.0;
    // phase-c
    modulating_index_0.sm1_c = 1.0;
    modulating_index_0.sm2_c = 1.0;
    modulating_index_0.sm3_c = 1.0;

    return modulating_index_0;
}



/*
 * function:  init_modulating_index_custom1
 * --------------------
 * Description: modulating index customized initialization for each cell
 *
 * inputs______
 *
 * outputs_____
 * 1) modulating_index_0: a structure of customized modulating indexes
 *
 */
struct signal_x_sm init_modulating_index_custom1(void)
{
    struct signal_x_sm modulating_index_0;
    // phase-a
    modulating_index_0.sm1_a = 0.95;   // 1.00
    modulating_index_0.sm2_a = 0.70;   // 0.80
    modulating_index_0.sm3_a = 0.80;   // 1.20
    // phase-b
    modulating_index_0.sm1_b = 1.0;
    modulating_index_0.sm2_b = 1.0;
    modulating_index_0.sm3_b = 1.0;
    // phase-c
    modulating_index_0.sm1_c = 1.0;
    modulating_index_0.sm2_c = 1.0;
    modulating_index_0.sm3_c = 1.0;

    return modulating_index_0;
}



/*
 * function:  init_ps_angles
 * --------------------
 * Description: ps angles standard init for 3 cells per phase. 
 * Angles are in degrees
 *
 * inputs______
 * 1) mode: defines the setting of the initialization
 * 
 * outputs_____
 * 1) ps_angles_0: a structure of modulating indexes all init in 1
 *
 */
struct signal_x_sm init_ps_angles(unsigned int mode)
{
    struct signal_x_sm ps_angles_0 = {0};
    if (mode == 0)
    {
        // phase-a
        ps_angles_0.sm1_a = 0;
        ps_angles_0.sm2_a = 60;
        ps_angles_0.sm3_a = 120;
        // phase-b
        ps_angles_0.sm1_b = 0;
        ps_angles_0.sm2_b = 60;
        ps_angles_0.sm3_b = 120;
        // phase-c
        ps_angles_0.sm1_c = 0;
        ps_angles_0.sm2_c = 60;
        ps_angles_0.sm3_c = 120;
    }

    if (mode == 1)
    {
        // phase-a
        ps_angles_0.sm1_a = 0;
        ps_angles_0.sm2_a = 113.76 * 0.5;
        ps_angles_0.sm3_a = 248.16 * 0.5;
        // phase-b
        ps_angles_0.sm1_b = 0;
        ps_angles_0.sm2_b = 60;
        ps_angles_0.sm3_b = 120;
        // phase-c
        ps_angles_0.sm1_c = 0;
        ps_angles_0.sm2_c = 60;
        ps_angles_0.sm3_c = 120;
    }

    return ps_angles_0;
}



/*
 * function:  init_PRcontroller
 * --------------------
 * Description: duty cycles variable initialization
 *
 * inputs______
 * 1) Vdc: maximum dc voltage in the arm
 * 2) R: load resistance
 * 3) L: filter inductance
 * 4) w_zero: grid frequency
 * 5) damping: controller's damping factor
 * 6) fs_pr: controller's sampling time
 *
 * outputs_____
 * 1) PRcontroller: a structure with zero previous error and PR default gains
 *
 */
struct PRcontroller init_PRcontroller(float Vdc, float R, float L, float w_zero, float damping, float fs_pr)
{
    // create structure to store controller paramaters
    struct PRcontroller PRcontroller = {0};

    // inverter plant
    float K_zero = ((float) Vdc) / ((float) R);
    float tau_zero = ((float) L) / ((float) R);

    // design parameters
    float Ts_pr = ((float) 1) / ((float) fs_pr);
    float wn_pr = ((float) fs_pr * 0.5) / ((float) 2 * damping);
    float Ti_pr = 2 * ((float) damping) / ((float) wn_pr);
    float Kp_pr = wn_pr * wn_pr * tau_zero * ((float) Ti_pr) / ((float) K_zero);
    float Ki_pr = ((float) Kp_pr) / ((float) Ti_pr);

    // compute discrete-time gains
    PRcontroller.a_0 = Kp_pr;
    PRcontroller.a_1 = 2 * ((((float) Ki_pr) / ((float) w_zero)) * sinf(w_zero * Ts_pr) - Kp_pr * cosf(w_zero * Ts_pr));
    PRcontroller.a_2 = Kp_pr - 2 * Ki_pr * ((float) sinf(w_zero * Ts_pr)) / ((float) w_zero);
    PRcontroller.b_1 = 2 * cosf(w_zero * Ts_pr);

    return PRcontroller;
}



/*
 * function:  init_PIcontroller
 * --------------------
 * Description: PI controller initialization with gain calculation
 *
 * inputs______
 * 1) Vdc: maximum dc voltage in the arm
 * 2) R: load resistance
 * 3) L: filter inductance
 * 4) w_zero: grid frequency
 * 5) damping: controller's damping factor
 * 6) fs_pr: controller's sampling time
 *
 * outputs_____
 * 1) PRcontroller: a structure with zero previous error and PR default gains
 *
 */
struct PIcontroller init_PIcontroller(float Vdc, float R, float L, float damping, float fs_pi, float gain)
{
    // create structure to store controller paramaters
    struct PIcontroller PIcontroller = {0};

    // inverter plant
    float K_zero = ((float) Vdc) / ((float) R);
    float tau_zero = ((float) L) / ((float) R);

    // design parameters
    float Ts_pi = ((float) 1) / ((float) fs_pi);
    float wn_pi = ((float) gain*fs_pi) / ((float) 2 * damping);
    float Ti_pi = 2.0 * ((float) damping) / ((float) wn_pi);
    float Kp_pi = wn_pi * wn_pi * tau_zero * ((float) Ti_pi) / ((float) K_zero);
    float Ki_pi = ((float) Kp_pi) / ((float) Ti_pi);

    // compute discrete-time gains
    PIcontroller.k_a = Kp_pi;
    PIcontroller.k_b = Ki_pi*Ts_pi - Kp_pi;

    return PIcontroller;
}



/*
 * function:  init_DigitalOutputs
 * --------------------
 * Description: selection of pins for digital outputs
 *
 * inputs______
 *
 * outputs_____
 *
 */
void init_DigitalOutputs(struct DigitalOutputs *DigitalOutputs)
{
    // Enables
    DigitalOutputs->EN1 = 26;
    DigitalOutputs->EN2 = 27;
    // Debug pins
    DigitalOutputs->comp_time = 64;
    DigitalOutputs->trigger = 25;
}

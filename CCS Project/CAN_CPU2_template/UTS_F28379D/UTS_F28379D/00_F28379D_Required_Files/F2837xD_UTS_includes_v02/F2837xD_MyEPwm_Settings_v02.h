


/* PWM Setting Functions
 *
 * 1. Individual COMP settings have been added. (13/06/2021)
 * 2. PWM 8 has been added. (22/09/2021)
 * 3. Fast EPWM write functions added. (23/09/2021)
 * 4. Ts calculation fixed. (23/09/2021)
******************************************************************/

void set_ALL_ePWMs_SYMM_kHz(float);
void set_ALL_ePWMs_SYMM_COMP(float);
void set_ePWM_PS_DEG(unsigned int, float);
void set_ePWM_Freq_MULT(int,  int);

void EPWM_ALL_SYMM_SYNC(float);
void EPWM_ALL_SYMM_SYNC_COMP(float, float);
void EPWM_SYMM_SYNC_COMP_IND(float, float, unsigned int);
void EPWM_ALL_SAME_FQ(float);
void EPWM_ALL_SAME_DB(float);


void InitEPwm1(void);
void InitEPwm2(void);
void InitEPwm3(void);
void InitEPwm4(void);
void InitEPwm5(void);
void InitEPwm6(void);
void InitEPwm7(void);
void InitEPwm8(void);
void InitEPwm9(void);
void InitEPwm10(void);
void InitEPwm11(void);
void InitEPwm12(void);

void UpdateEPwm1(void);
void UpdateEPwm2(void);
void UpdateEPwm3(void);
void UpdateEPwm4(void);
void UpdateEPwm5(void);
void UpdateEPwm6(void);
void UpdateEPwm7(void);
void UpdateEPwm8(void);
void UpdateEPwm9(void);
void UpdateEPwm10(void);
void UpdateEPwm11(void);
void UpdateEPwm12(void);

void EPWM_IND(unsigned int, float);

void write_ePWMxA(unsigned int, float);
void write_ePWMxB(unsigned int, float);

void static inline write_ePWM1A(float);
void static inline write_ePWM2A(float);
void static inline write_ePWM3A(float);
void static inline write_ePWM4A(float);
void static inline write_ePWM5A(float);
void static inline write_ePWM6A(float);
void static inline write_ePWM7A(float);
void static inline write_ePWM8A(float);
void static inline write_ePWM9A(float);
void static inline write_ePWM10A(float);
void static inline write_ePWM11A(float);
void static inline write_ePWM12A(float);

void static inline write_ePWM1B(float);
void static inline write_ePWM2B(float);
void static inline write_ePWM3B(float);
void static inline write_ePWM4B(float);
void static inline write_ePWM5B(float);
void static inline write_ePWM6B(float);
void static inline write_ePWM7B(float);
void static inline write_ePWM8B(float);
void static inline write_ePWM9B(float);
void static inline write_ePWM10B(float);
void static inline write_ePWM11B(float);
void static inline write_ePWM12B(float);

void Inverting_PWMx_A(unsigned int pwm);
void Noninverting_PWMx_A(unsigned int pwm);
void Inverting_PWMx_B(unsigned int pwm);
void Noninverting_PWMx_B(unsigned int pwm);


/* My Functions
******************************************************************/

void set_ALL_ePWMs_SYMM_kHz(float freq)
{
    EPWM_ALL_SYMM_SYNC(freq);
}

/*
void set_ALL_ePWMs_SYMM_COMP(float dead_time)
{
    EPWM_ALL_SYMM_SYNC_COMP(EPWM_ALL_FQ,dead_time);
}
*/


void EPWM_ALL_SYMM_SYNC(float freq)
{
    EPWM_ALL_CMP = 0;
    EPWM_ALL_FQ = freq;
    //EPWM_ALL_PRD = 1000/freq;
    EPWMx_IND_FQ=0;

    EPWM_ALL_SAME_FQ(freq);
    EPWM_ALL_SAME_DB(0);

    // enable PWMs
    CpuSysRegs.PCLKCR2.bit.EPWM1=1;
    CpuSysRegs.PCLKCR2.bit.EPWM2=1;
    CpuSysRegs.PCLKCR2.bit.EPWM3=1;
    CpuSysRegs.PCLKCR2.bit.EPWM4=1;
    CpuSysRegs.PCLKCR2.bit.EPWM5=1;
    CpuSysRegs.PCLKCR2.bit.EPWM6=1;
    CpuSysRegs.PCLKCR2.bit.EPWM7=1;
    CpuSysRegs.PCLKCR2.bit.EPWM8=1;
    CpuSysRegs.PCLKCR2.bit.EPWM9=1;
    CpuSysRegs.PCLKCR2.bit.EPWM10=1;
    CpuSysRegs.PCLKCR2.bit.EPWM11=1;
    CpuSysRegs.PCLKCR2.bit.EPWM12=1;

    InitEPwmGpio();

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    InitEPwm1();
    InitEPwm2();
    InitEPwm3();
    InitEPwm4();
    InitEPwm5();
    InitEPwm6();
    InitEPwm7();
    InitEPwm8();
    InitEPwm9();
    InitEPwm10();
    InitEPwm11();
    InitEPwm12();

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

}

/*
void EPWM_ALL_SYMM_SYNC_COMP(float freq, float dead_time)
{
    int k;
    EPWM_ALL_CMP = 1;
    for(k=0; k<12; k++ ){
        EPWMx_COMP[k] = 1;
    }
    EPWM_ALL_FQ = freq;
    //EPWM_ALL_PRD = 1000/freq;
    EPWMx_IND_FQ = 0;
    EPWM_ALL_DB = dead_time;

    EPWM_ALL_SAME_FQ(freq);
    EPWM_ALL_SAME_DB(dead_time);

    // enable PWMs
    CpuSysRegs.PCLKCR2.bit.EPWM1=1;
    CpuSysRegs.PCLKCR2.bit.EPWM2=1;
    CpuSysRegs.PCLKCR2.bit.EPWM3=1;
    CpuSysRegs.PCLKCR2.bit.EPWM4=1;
    CpuSysRegs.PCLKCR2.bit.EPWM5=1;
    CpuSysRegs.PCLKCR2.bit.EPWM6=1;
    CpuSysRegs.PCLKCR2.bit.EPWM7=1;
    CpuSysRegs.PCLKCR2.bit.EPWM8=1;
    CpuSysRegs.PCLKCR2.bit.EPWM9=1;
    CpuSysRegs.PCLKCR2.bit.EPWM10=1;
    CpuSysRegs.PCLKCR2.bit.EPWM11=1;
    CpuSysRegs.PCLKCR2.bit.EPWM12=1;

    InitEPwmGpio();

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    InitEPwm1();
    InitEPwm2();
    InitEPwm3();
    InitEPwm4();
    InitEPwm5();
    InitEPwm6();
    InitEPwm7();
    InitEPwm8();
    InitEPwm9();
    InitEPwm10();
    InitEPwm11();
    InitEPwm12();

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

}
*/


/*
void EPWM_SYMM_SYNC_COMP_IND(float freq, float dead_time, unsigned int comp_settings)
{
    int k;
    EPWM_ALL_CMP = 1;
    for(k=0; k<12; k++ ){
        EPWMx_COMP[k] = (comp_settings & (1<<k))? 1 : 0;
    }

    EPWM_ALL_FQ = freq;
    //EPWM_ALL_PRD = 1000/freq;
    EPWMx_IND_FQ = 0;
    EPWM_ALL_DB = dead_time;

    EPWM_ALL_SAME_FQ(freq);
    EPWM_ALL_SAME_DB(dead_time);

    // enable PWMs
    CpuSysRegs.PCLKCR2.bit.EPWM1=1;
    CpuSysRegs.PCLKCR2.bit.EPWM2=1;
    CpuSysRegs.PCLKCR2.bit.EPWM3=1;
    CpuSysRegs.PCLKCR2.bit.EPWM4=1;
    CpuSysRegs.PCLKCR2.bit.EPWM5=1;
    CpuSysRegs.PCLKCR2.bit.EPWM6=1;
    CpuSysRegs.PCLKCR2.bit.EPWM7=1;
    CpuSysRegs.PCLKCR2.bit.EPWM8=1;
    CpuSysRegs.PCLKCR2.bit.EPWM9=1;
    CpuSysRegs.PCLKCR2.bit.EPWM10=1;
    CpuSysRegs.PCLKCR2.bit.EPWM11=1;
    CpuSysRegs.PCLKCR2.bit.EPWM12=1;

    InitEPwmGpio();

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    InitEPwm1();
    InitEPwm2();
    InitEPwm3();
    InitEPwm4();
    InitEPwm5();
    InitEPwm6();
    InitEPwm7();
    InitEPwm8();
    InitEPwm9();
    InitEPwm10();
    InitEPwm11();
    InitEPwm12();

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

}
*/

void EPWM_ALL_SAME_FQ(float freq)
{
    int k=0;
    int pwm_ind=0;

    float amp_freq;



    for(k=0; k<12; k++ ){
        pwm_ind = (EPWMx_IND_FQ >>k)&1;
        if (pwm_ind==0){
            amp_freq = EPWMx_FQ_MULT[k]*freq;
            if (EPWM_ALL_TYPE == 0)
                EPWM_ALL_TMAX=(unsigned int)(0.5*CLK_FQ/amp_freq);
            else
                EPWM_ALL_TMAX=(unsigned int)(CLK_FQ/amp_freq);
            EPWMx_FQ[k]=amp_freq;
            EPWMx_TMAX[k]=EPWM_ALL_TMAX;
            }
        }

}

void EPWM_ALL_SAME_DB(float dead_time)
{
    int k=0;
    for(k=0; k<12; k++ ){
        EPWMx_DB[k]=dead_time;
    }
    EPWM_ALL_DB = dead_time;
}

void set_ePWM_PS_DEG(unsigned int pwm, float ps_deg)
{
    if (ps_deg < -360)
        ps_deg = 0;
    if (ps_deg < 0)
        ps_deg = 360 + ps_deg;
    if (ps_deg>=360)
        ps_deg = 0;

    if (pwm<13){
        
        EPWMx_PS_DEG[pwm-1] = ps_deg;
        if (ps_deg > 180) //180
        {
            ps_deg = 360 - ps_deg;
            EPWMx_PHSDIR[pwm-1] = 1;
        }
        else
            EPWMx_PHSDIR[pwm-1] = 0;
        if (EPWM_ALL_TYPE == 0)
            EPWMx_PS[pwm-1]=(unsigned int)(round(EPWMx_TMAX[pwm-1]*ps_deg*0.005555555555556));
        else
            EPWMx_PS[pwm-1]=(unsigned int)(round(EPWMx_TMAX[pwm-1]*ps_deg*0.002777777777778));
    }
}


void set_ePWM_PS_DEG_VA(unsigned int pwm, float ps_deg)
{
    // angles are constrained between 0 and 120 for 3 cells
    if (ps_deg < 0)
        ps_deg = 0;
    if (ps_deg > 180)
        ps_deg = 180;

    if (pwm<13){
        
        EPWMx_PS_DEG[pwm-1] = ps_deg;

        // counter direction sync with EPWM7
        // EPWMx_PHSDIR[pwm-1] = 1 - EPWMx_PHSDIR[6]; // inverse polarity due to delay
        EPWMx_PHSDIR[pwm-1] =  EPWMx_PHSDIR[6]; // equal polarity
        EPWMx_PS[pwm-1]=(unsigned int)(round(EPWMx_TMAX[pwm-1]*ps_deg*0.005555555555556)); // symmetric
    }
}


void set_ePWM_Freq_MULT( int pwm,  int gain){
    float amp_freq;

    if (gain<1)
        gain = 1;

    EPWMx_FQ_MULT[pwm-1]=gain;

    amp_freq = EPWMx_FQ_MULT[pwm-1]*EPWMx_FQ[pwm-1];

    if (EPWM_ALL_TYPE == 0)
        EPWMx_TMAX[pwm-1]=(unsigned int)(0.5*CLK_FQ/amp_freq);
    else
        EPWMx_TMAX[pwm-1]=(unsigned int)(CLK_FQ/amp_freq);

}
 

void EPWM_IND(unsigned int pwm, float freq){
    if (pwm>0 && pwm<13){

        EPWMx_IND_FQ = (EPWMx_IND_FQ & ~(1 << pwm-1)) | (1 << pwm-1);
        EPWMx_FQ[pwm-1] = freq;

        if (EPWM_ALL_TYPE == 0)
            EPWMx_TMAX[pwm-1]=(unsigned int)(0.5*CLK_FQ/freq);
        else
            EPWMx_TMAX[pwm-1]=(unsigned int)(CLK_FQ/freq);
    }
}




void write_ePWMxA(unsigned int pwm, float d)
{
    unsigned int out =0;

    if (d<0)
        d=0;
    if (d>1)
        d=1;

    out = (unsigned int)(d*EPWMx_TMAX[pwm-1]);

    if (pwm==1)
        EPwm1Regs.CMPA.bit.CMPA  = out;     // adjust duty for output EPWM1A

    if (pwm==2)
        EPwm2Regs.CMPA.bit.CMPA  = out;     // adjust duty for output EPWM2A

    if (pwm==3)
        EPwm3Regs.CMPA.bit.CMPA  = out;     // adjust duty for output EPWM3A

    if (pwm==4)
        EPwm4Regs.CMPA.bit.CMPA  = out;     // adjust duty for output EPWM4A

    if (pwm==5)
        EPwm5Regs.CMPA.bit.CMPA  = out;     // adjust duty for output EPWM5A

    if (pwm==6)
        EPwm6Regs.CMPA.bit.CMPA  = out;     // adjust duty for output EPWM6A

    if (pwm==7)
        EPwm7Regs.CMPA.bit.CMPA  = out;     // adjust duty for output EPWM7A

    if (pwm==8)
        EPwm8Regs.CMPA.bit.CMPA  = out;     // adjust duty for output EPWM8A

    if (pwm==9)
        EPwm9Regs.CMPA.bit.CMPA  = out;     // adjust duty for output EPWM9A

    if (pwm==10)
        EPwm10Regs.CMPA.bit.CMPA = out;     // adjust duty for output EPWM10A

    if (pwm==11)
        EPwm11Regs.CMPA.bit.CMPA = out;    // adjust duty for output EPWM11A

    if (pwm==12)
        EPwm12Regs.CMPA.bit.CMPA = out;    // adjust duty for output EPWM12A

}


void write_ePWMxB(unsigned int pwm, float d)
{
    unsigned int out =0;

    if (d<0)
        d=0;
    if (d>1)
        d=1;

    out = (unsigned int)(d*EPWMx_TMAX[pwm-1]);

    if (pwm==1)
        EPwm1Regs.CMPB.bit.CMPB  = out;     // adjust duty for output EPWM1B

    if (pwm==2)
        EPwm2Regs.CMPB.bit.CMPB  = out;     // adjust duty for output EPWM2B

    if (pwm==3)
        EPwm3Regs.CMPB.bit.CMPB  = out;     // adjust duty for output EPWM3B

    if (pwm==4)
        EPwm4Regs.CMPB.bit.CMPB  = out;     // adjust duty for output EPWM4B

    if (pwm==5)
        EPwm5Regs.CMPB.bit.CMPB  = out;     // adjust duty for output EPWM5B

    if (pwm==6)
        EPwm6Regs.CMPB.bit.CMPB  = out;     // adjust duty for output EPWM6B

    if (pwm==7)
        EPwm7Regs.CMPB.bit.CMPB  = out;     // adjust duty for output EPWM7A

    if (pwm==8)
        EPwm8Regs.CMPB.bit.CMPB  = out;     // adjust duty for output EPWM8A

    if (pwm==9)
        EPwm9Regs.CMPB.bit.CMPB  = out;     // adjust duty for output EPWM9A

    if (pwm==10)
        EPwm10Regs.CMPB.bit.CMPB = out;     // adjust duty for output EPWM10A

    if (pwm==11)
        EPwm11Regs.CMPB.bit.CMPB = out;    // adjust duty for output EPWM11A

    if (pwm==12)
        EPwm12Regs.CMPB.bit.CMPB = out;    // adjust duty for output EPWM12A

}

/*
// Fast EPWM Write
void static inline write_ePWM1A(float d)
{
    EPwm1Regs.CMPA.bit.CMPA  = (unsigned int)(d*EPWMx_TMAX[0]);
}

void static inline write_ePWM2A(float d)
{
    EPwm2Regs.CMPA.bit.CMPA  = (unsigned int)(d*EPWMx_TMAX[1]);
}

void static inline write_ePWM3A(float d)
{
    EPwm3Regs.CMPA.bit.CMPA  = (unsigned int)(d*EPWMx_TMAX[2]);
}

void static inline write_ePWM4A(float d)
{
    EPwm4Regs.CMPA.bit.CMPA  = (unsigned int)(d*EPWMx_TMAX[3]);
}

void static inline write_ePWM5A(float d)
{
    EPwm5Regs.CMPA.bit.CMPA  = (unsigned int)(d*EPWMx_TMAX[4]);
}

void static inline write_ePWM6A(float d)
{
    EPwm6Regs.CMPA.bit.CMPA  = (unsigned int)(d*EPWMx_TMAX[5]);
}

void static inline write_ePWM7A(float d)
{
    EPwm7Regs.CMPA.bit.CMPA  = (unsigned int)(d*EPWMx_TMAX[6]);
}

void static inline write_ePWM8A(float d)
{
    EPwm8Regs.CMPA.bit.CMPA  = (unsigned int)(d*EPWMx_TMAX[7]);
}

void static inline write_ePWM9A(float d)
{
    EPwm9Regs.CMPA.bit.CMPA  = (unsigned int)(d*EPWMx_TMAX[8]);
}

void static inline write_ePWM10A(float d)
{
    EPwm10Regs.CMPA.bit.CMPA  = (unsigned int)(d*EPWMx_TMAX[9]);
}

void static inline write_ePWM11A(float d)
{
    EPwm11Regs.CMPA.bit.CMPA  = (unsigned int)(d*EPWMx_TMAX[10]);
}

void static inline write_ePWM12A(float d)
{
    EPwm12Regs.CMPA.bit.CMPA  = (unsigned int)(d*EPWMx_TMAX[11]);
}


void static inline write_ePWM1B(float d)
{
    EPwm1Regs.CMPB.bit.CMPB  = (unsigned int)(d*EPWMx_TMAX[0]);
}

void static inline write_ePWM2B(float d)
{
    EPwm2Regs.CMPB.bit.CMPB  = (unsigned int)(d*EPWMx_TMAX[1]);
}

void static inline write_ePWM3B(float d)
{
    EPwm3Regs.CMPB.bit.CMPB  = (unsigned int)(d*EPWMx_TMAX[2]);
}

void static inline write_ePWM4B(float d)
{
    EPwm4Regs.CMPB.bit.CMPB  = (unsigned int)(d*EPWMx_TMAX[3]);
}

void static inline write_ePWM5B(float d)
{
    EPwm5Regs.CMPB.bit.CMPB  = (unsigned int)(d*EPWMx_TMAX[4]);
}

void static inline write_ePWM6B(float d)
{
    EPwm6Regs.CMPB.bit.CMPB  = (unsigned int)(d*EPWMx_TMAX[5]);
}

void static inline write_ePWM7B(float d)
{
    EPwm7Regs.CMPB.bit.CMPB  = (unsigned int)(d*EPWMx_TMAX[6]);
}

void static inline write_ePWM8B(float d)
{
    EPwm8Regs.CMPB.bit.CMPB  = (unsigned int)(d*EPWMx_TMAX[7]);
}

void static inline write_ePWM9B(float d)
{
    EPwm9Regs.CMPB.bit.CMPB  = (unsigned int)(d*EPWMx_TMAX[8]);
}

void static inline write_ePWM10B(float d)
{
    EPwm10Regs.CMPB.bit.CMPB  = (unsigned int)(d*EPWMx_TMAX[9]);
}

void static inline write_ePWM11B(float d)
{
    EPwm11Regs.CMPB.bit.CMPB  = (unsigned int)(d*EPWMx_TMAX[10]);
}

void static inline write_ePWM12B(float d)
{
    EPwm12Regs.CMPB.bit.CMPB  = (unsigned int)(d*EPWMx_TMAX[11]);
}
*/




/* PWM Initialization
******************************************************************/

// InitEPwm1 - Initialize EPWM1 configuration
//
void InitEPwm1()
{
    // Set Clock
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm1Regs.TBPRD = EPWMx_TMAX[0];           // Set timer period (Max Count)
    EPwm1Regs.TBPHS.bit.TBPHS = EPWMx_PS[0];   // Phase is 0
    EPwm1Regs.TBCTR = 0x0000;                  // Clear counter

    // Set Compare values
    EPwm1Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm1Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Setup counter mode
    EPWMx_PHSDIR[0] = 0;
    EPwm1Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[0];            // Start Counting Up
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up and down
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // (Master) Disable phase loading
    EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_CMPB;    // (Master) Sync down-stream module to sync EPWM2 TB_CTR_CMPB, TB_CTR_ZERO

    // Dead Time
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;

    // Setup shadowing: When CMPA and CMPB will be implemented
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD; // (Double Update) Load on Zero and Period CC_CTR_ZERO CC_CTR_ZERO_PRD
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;


    // PWM Logic
    //************************
    // EPWM1A Positive
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM1A
    EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;

    // EPWM1B Positive
    EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM1B
    EPwm1Regs.AQCTLB.bit.CBD = AQ_SET;

    // EPWM1B Negative
    //EPwm1Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM1B
    //EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;


    // Timer Interrupt
    //EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // (single update) Select INT on Zero event
    //EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;     // (single update) Select INT on Period (Max count) event

    #ifdef SINGLE_UPDATE_EPWM_INIT
        EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // (single update) Select INT on Zero event
    #else
        EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRDZERO;  // (double update) Select INT on Zero and Period (Max count) event
    #endif

    EPwm1Regs.ETSEL.bit.INTEN = 1;                // Enable INT
    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event

    //SyncSocRegs.SYNCSELECT.bit.EPWM4SYNCIN = 0b000;
    //SyncSocRegs.SYNCSELECT.bit.EPWM7SYNCIN = 0b000;
    //SyncSocRegs.SYNCSELECT.bit.EPWM10SYNCIN = 0b000;

}

//
// InitEPwm2 - Initialize EPWM2 configuration
//
void InitEPwm2()
{
    // Set Clock
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm2Regs.TBPRD = EPWMx_TMAX[1];             // Set timer period (Max Count)
    EPwm2Regs.TBPHS.bit.TBPHS = EPWMx_PS[1];     // Phase Shift (initial counter value)
    EPwm2Regs.TBCTR = 0x0000;                    // Clear counter

    // Set Compare values
    EPwm2Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm2Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Setup counter mode
    EPwm2Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[1];   // Set Initial Count Direction
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up and down -- Symmetric PWM /\/\/
    EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;          // Enable phase loading
    EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;          // Upload duty-cycle in the next sampling
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // sync flow-through to sync EPWM3

    // Dead Time
    EPwm2Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;

    // Setup shadowing
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD; // (Double Update) Load on Zero and Period
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    // PWM Logic
    //************************
    // EPWM2A Positive
    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM2A
    EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;

    // EPWM2B Positive
    EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM2B
    EPwm2Regs.AQCTLB.bit.CBD = AQ_SET;

    // EPWM2B Negative
    //EPwm2Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM2B
    //EPwm2Regs.AQCTLB.bit.CBD = AQ_CLEAR;

    // Timer Interrupt
    //EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // (single update) Select INT on Zero event
    //EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;     // (single update) Select INT on Period (Max count) event

    #ifdef SINGLE_UPDATE_EPWM_INIT
        EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // (single update) Select INT on Zero event
    #else
        EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_PRDZERO;  // (double update) Select INT on Zero and Period (Max count) event
    #endif

    EPwm2Regs.ETSEL.bit.INTEN = 1;                // Enable INT
    EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event

}

//
// InitEPwm3 - Initialize EPWM3 configuration
//
void InitEPwm3()
{
    // Set Clock
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm3Regs.TBPRD = EPWMx_TMAX[2];             // Set timer period (Max Count)
    EPwm3Regs.TBPHS.bit.TBPHS = EPWMx_PS[2];     // Phase Shift (initial counter value)
    EPwm3Regs.TBCTR = 0x0000;                    // Clear counter

    // Set Compare values
    EPwm3Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm3Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Setup counter mode
    EPwm3Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[2];   // Set Initial Count Direction
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up and down -- Symmetric PWM /\/\/
    EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;          // Enable phase loading
    EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;          // Upload duty-cycle in the next sampling
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // sync flow-through to sync EPWM4

    // Dead Time
    EPwm3Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;

    // Setup shadowing
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD; // (Double Update) Load on Zero and Period
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    // PWM Logic
    //************************
    // EPWM3A Positive
    EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM3A
    EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;

    // EPWM3B Positive
    EPwm3Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM3B
    EPwm3Regs.AQCTLB.bit.CBD = AQ_SET;

    // EPWM3B Negative
    //EPwm3Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM3B
    //EPwm3Regs.AQCTLB.bit.CBD = AQ_CLEAR;

    // Timer Interrupt
    //EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // (single update) Select INT on Zero event
    //EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;     // (single update) Select INT on Period (Max count) event

    #ifdef SINGLE_UPDATE_EPWM_INIT
        EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // (single update) Select INT on Zero event
    #else
        EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_PRDZERO;  // (double update) Select INT on Zero and Period (Max count) event
    #endif

    EPwm3Regs.ETSEL.bit.INTEN = 1;                // Enable INT
    EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
}

void InitEPwm4()
{
    // Set Clock
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm4Regs.TBPRD = EPWMx_TMAX[3];             // Set timer period (Max Count)
    EPwm4Regs.TBPHS.bit.TBPHS = EPWMx_PS[3];     // Phase Shift (initial counter value)
    EPwm4Regs.TBCTR = 0x0000;                    // Clear counter

    // Set Compare values
    EPwm4Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm4Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Setup counter mode
    EPwm4Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[3];   // Set Initial Count Direction
    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up and down -- Symmetric PWM /\/\/
    EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;          // Enable phase loading
    EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW;          // Upload duty-cycle in the next sampling
    EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // sync flow-through to sync EPWM5 TB_SYNC_DISABLE   TB_SYNC_IN

    // Dead Time
    EPwm4Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;


    // Setup shadowing
    EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD; // (Double Update) Load on Zero and Period
    EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    // PWM Logic
    //************************
    // EPWM4A Positive
    EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM4A
    EPwm4Regs.AQCTLA.bit.CAD = AQ_SET;

    // EPWM4B Positive
    EPwm4Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM4B
    EPwm4Regs.AQCTLB.bit.CBD = AQ_SET;

    // EPWM4B Negative
    //EPwm4Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM4B
    //EPwm4Regs.AQCTLB.bit.CBD = AQ_CLEAR;

    // Timer Interrupt
    //EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // (single update) Select INT on Zero event
    //EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;     // (single update) Select INT on Period (Max count) event
    EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_PRDZERO;  // (double update) Select INT on Zero and Period event
    EPwm4Regs.ETSEL.bit.INTEN = 1;                // Enable INT
    EPwm4Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event

}

void InitEPwm5()
{
    EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm5Regs.TBPRD = EPWMx_TMAX[4];             // Set timer period 801 TBCLKs
    EPwm5Regs.TBPHS.bit.TBPHS = EPWMx_PS[4];     // Phase is 0
    EPwm5Regs.TBCTR = 0x0000;                    // Clear counter

    // Set Compare values
    EPwm5Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm5Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Setup counter mode
    EPwm5Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[4];
    EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up and down
    EPwm5Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Enable phase loading
    EPwm5Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // sync flow-through to sync EPWM5

    // Dead Time
    EPwm4Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;


    // Setup shadowing
    EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD; // (Double Update) Load on Zero and Period
    EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    // PWM Logic
    //************************
    // EPWM4A Positive
    EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM4A
    EPwm5Regs.AQCTLA.bit.CAD = AQ_SET;

    // EPWM4B Positive
    EPwm5Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM4B
    EPwm5Regs.AQCTLB.bit.CBD = AQ_SET;

    // EPWM4B Negative
    //EPwm4Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM4B
    //EPwm4Regs.AQCTLB.bit.CBD = AQ_CLEAR;


    // Interrupt where we will change the Compare Values
    //
    //EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;    // Select INT on Zero event
    EPwm5Regs.ETSEL.bit.INTSEL = ET_CTR_PRDZERO;  // (double update) Select INT on Zero and Period event
    EPwm5Regs.ETSEL.bit.INTEN = 1;                // Enable INT
    EPwm5Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event

}
//
// InitEPwm6 - Initialize EPWM3 configuration
//
void InitEPwm6()
{
    // Set Clock
    EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm6Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Set Compare values
    EPwm6Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm6Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Setup counter mode
    EPwm6Regs.TBCTR = 0x0000;                       // Clear counter
    EPwm6Regs.TBPRD = EPWMx_TMAX[5];                // Set Max Count

    EPwm6Regs.TBPHS.bit.TBPHS = EPWMx_PS[5];        // Phase Shift (initial counter value)
    EPwm6Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[5];   // Set Initial Count Direction
    EPwm6Regs.TBCTL.bit.PHSEN = TB_ENABLE;           // Enable phase loading
    EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up and down -- Symmetric PWM /\/\/\

    EPwm6Regs.TBCTL.bit.PRDLD = TB_SHADOW;          // Upload duty-cycle in the next sampling
    EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // sync flow-through to sync EPWM7

    // Dead Time
    EPwm6Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;


    // Setup shadowing
    EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD; // (Double Update) Load on Zero and Period
    EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    // PWM Logic
    //************************
    // EPWM6A Positive
    EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM6A
    EPwm6Regs.AQCTLA.bit.CAD = AQ_SET;

    // EPWM6B Positive
    EPwm6Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM6B
    EPwm6Regs.AQCTLB.bit.CBD = AQ_SET;

    // EPWM6B Negative
    //EPwm6Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM6B
    //EPwm6Regs.AQCTLB.bit.CBD = AQ_CLEAR;


    // Interrupt where we will change the Compare Values
    //
    //EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;    // Select INT on Zero event
    EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_PRDZERO;  // (double update) Select INT on Zero and Period event
    EPwm6Regs.ETSEL.bit.INTEN = 1;                // Enable INT
    EPwm6Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event

}
//
// InitEPwm7 - Initialize EPWM7 configuration
//
void InitEPwm7()
{
    // Set Clock
    EPwm7Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm7Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Set Compare values
    EPwm7Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm7Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Setup counter mode
    EPwm7Regs.TBCTR = 0x0000;                       // Clear counter
    EPwm7Regs.TBPRD = EPWMx_TMAX[6];                // Set Max Count

    EPwm7Regs.TBPHS.bit.TBPHS = EPWMx_PS[6];        // Phase Shift (initial counter value)
    EPwm7Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[6];   // Set Initial Count Direction
    EPwm7Regs.TBCTL.bit.PHSEN = TB_ENABLE;           // Enable phase loading
    EPwm7Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up and down -- Symmetric PWM /\/\/\

    EPwm7Regs.TBCTL.bit.PRDLD = TB_SHADOW;          // Upload duty-cycle in the next sampling
    EPwm7Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // sync flow-through to sync EPWM7

    // Dead Time
    EPwm7Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;


    // Setup shadowing
    EPwm7Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm7Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm7Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD; // (Double Update) Load on Zero and Period
    EPwm7Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    // PWM Logic
    //************************
    // EPWM7A Positive
    EPwm7Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM7A
    EPwm7Regs.AQCTLA.bit.CAD = AQ_SET;

    // EPWM7B Positive
    EPwm7Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM7B
    EPwm7Regs.AQCTLB.bit.CBD = AQ_SET;

    // EPWM7B Negative
    //EPwm7Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM7B
    //EPwm7Regs.AQCTLB.bit.CBD = AQ_CLEAR;


    // Interrupt where we will change the Compare Values
    //
    //EPwm7Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;    // Select INT on Zero event
    EPwm7Regs.ETSEL.bit.INTSEL = ET_CTR_PRDZERO;  // (double update) Select INT on Zero and Period event
    EPwm7Regs.ETSEL.bit.INTEN = 1;                // Enable INT
    EPwm7Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event

}
//
// InitEPwm8 - Initialize EPWM3 configuration
//
void InitEPwm8()
{
    // Set Clock
    EPwm8Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm8Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Set Compare values
    EPwm8Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm8Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Setup counter mode
    EPwm8Regs.TBCTR = 0x0000;                       // Clear counter
    EPwm8Regs.TBPRD = EPWMx_TMAX[7];                // Set Max Count

    EPwm8Regs.TBPHS.bit.TBPHS = EPWMx_PS[7];        // Phase Shift (initial counter value)
    EPwm8Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[7];   // Set Initial Count Direction
    EPwm8Regs.TBCTL.bit.PHSEN = TB_ENABLE;           // Enable phase loading
    EPwm8Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up and down -- Symmetric PWM /\/\/\

    EPwm8Regs.TBCTL.bit.PRDLD = TB_SHADOW;          // Upload duty-cycle in the next sampling
    EPwm8Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // sync flow-through to sync EPWM7

    // Dead Time
    EPwm8Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;


    // Setup shadowing
    EPwm8Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm8Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm8Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD; // (Double Update) Load on Zero and Period
    EPwm8Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    // PWM Logic
    //************************
    // EPWM8A Positive
    EPwm8Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM8A
    EPwm8Regs.AQCTLA.bit.CAD = AQ_SET;

    // EPWM8B Positive
    EPwm8Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM8B
    EPwm8Regs.AQCTLB.bit.CBD = AQ_SET;

    // EPWM8B Negative
    //EPwm8Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM8B
    //EPwm8Regs.AQCTLB.bit.CBD = AQ_CLEAR;


    // Interrupt where we will change the Compare Values
    //
    //EPwm8Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;    // Select INT on Zero event
    EPwm8Regs.ETSEL.bit.INTSEL = ET_CTR_PRDZERO;  // (double update) Select INT on Zero and Period event
    EPwm8Regs.ETSEL.bit.INTEN = 1;                // Enable INT
    EPwm8Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
}
//
// InitEPwm9 - Initialize EPWM9 configuration
//
void InitEPwm9()
{
    // Set Clock
    EPwm9Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm9Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Set Compare values
    EPwm9Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm9Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Setup counter mode
    EPwm9Regs.TBCTR = 0x0000;                       // Clear counter
    EPwm9Regs.TBPRD = EPWMx_TMAX[8];                // Set Max Count

    EPwm9Regs.TBPHS.bit.TBPHS = EPWMx_PS[8];        // Phase Shift (initial counter value)
    EPwm9Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[8];   // Set Initial Count Direction
    EPwm9Regs.TBCTL.bit.PHSEN = TB_ENABLE;           // Enable phase loading
    EPwm9Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up and down -- Symmetric PWM /\/\/\

    EPwm9Regs.TBCTL.bit.PRDLD = TB_SHADOW;          // Upload duty-cycle in the next sampling
    EPwm9Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // sync flow-through to sync EPWM9

    // Dead Time
    EPwm9Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;


    // Setup shadowing
    EPwm9Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm9Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm9Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD; // (Double Update) Load on Zero and Period
    EPwm9Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    // PWM Logic
    //************************
    // EPWM9A Positive
    EPwm9Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM9A
    EPwm9Regs.AQCTLA.bit.CAD = AQ_SET;

    // EPWM9B Positive
    EPwm9Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM9B
    EPwm9Regs.AQCTLB.bit.CBD = AQ_SET;

    // EPWM6B Negative
    //EPwm9Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM9B
    //EPwm9Regs.AQCTLB.bit.CBD = AQ_CLEAR;


    // Interrupt where we will change the Compare Values
    //
    //EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;    // Select INT on Zero event
    EPwm9Regs.ETSEL.bit.INTSEL = ET_CTR_PRDZERO;  // (double update) Select INT on Zero and Period event
    EPwm9Regs.ETSEL.bit.INTEN = 1;                // Enable INT
    EPwm9Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
}
//
// InitEPwm10 - Initialize EPWM10 configuration
//
void InitEPwm10()
{
    // Set Clock
    EPwm10Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm10Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Set Compare values
    EPwm10Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm10Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Setup counter mode
    EPwm10Regs.TBCTR = 0x0000;                       // Clear counter
    EPwm10Regs.TBPRD = EPWMx_TMAX[9];                // Set Max Count

    EPwm10Regs.TBPHS.bit.TBPHS = EPWMx_PS[9];        // Phase Shift (initial counter value)
    EPwm10Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[9];   // Set Initial Count Direction
    EPwm10Regs.TBCTL.bit.PHSEN = TB_ENABLE;           // Enable phase loading
    EPwm10Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up and down -- Symmetric PWM /\/\/\

    EPwm10Regs.TBCTL.bit.PRDLD = TB_SHADOW;          // Upload duty-cycle in the next sampling
    EPwm10Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // sync flow-through to sync EPWM7

    // Dead Time
    EPwm10Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;


    // Setup shadowing
    EPwm10Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm10Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm10Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD; // (Double Update) Load on Zero and Period
    EPwm10Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    // PWM Logic
    //************************
    // EPWM10A Positive
    EPwm10Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM10A
    EPwm10Regs.AQCTLA.bit.CAD = AQ_SET;

    // EPWM10B Positive
    EPwm10Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM10B
    EPwm10Regs.AQCTLB.bit.CBD = AQ_SET;

    // EPWM10B Negative
    //EPwm10Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM10B
    //EPwm10Regs.AQCTLB.bit.CBD = AQ_CLEAR;


    // Interrupt where we will change the Compare Values
    //
    //EPwm10Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;    // Select INT on Zero event
    EPwm10Regs.ETSEL.bit.INTSEL = ET_CTR_PRDZERO;  // (double update) Select INT on Zero and Period event
    EPwm10Regs.ETSEL.bit.INTEN = 1;                // Enable INT
    EPwm10Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
}
//
// InitEPwm11 - Initialize EPWM11 configuration
//
void InitEPwm11()
{
    // Set Clock
    EPwm11Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm11Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Set Compare values
    EPwm11Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm11Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Setup counter mode
    EPwm11Regs.TBCTR = 0x0000;                       // Clear counter
    EPwm11Regs.TBPRD = EPWMx_TMAX[10];                // Set Max Count

    EPwm11Regs.TBPHS.bit.TBPHS = EPWMx_PS[10];        // Phase Shift (initial counter value)
    EPwm11Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[10];   // Set Initial Count Direction
    EPwm11Regs.TBCTL.bit.PHSEN = TB_ENABLE;           // Enable phase loading        
    EPwm11Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up and down -- Symmetric PWM /\/\/\

    EPwm11Regs.TBCTL.bit.PRDLD = TB_SHADOW;          // Upload duty-cycle in the next sampling
    EPwm11Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // sync flow-through to sync EPWM7

    // Dead Time
    EPwm11Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;


    // Setup shadowing
    EPwm11Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm11Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm11Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD; // (Double Update) Load on Zero and Period
    EPwm11Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    // PWM Logic
    //************************
    // EPWM11A Positive
    EPwm11Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM11A
    EPwm11Regs.AQCTLA.bit.CAD = AQ_SET;

    // EPWM11B Positive
    EPwm11Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM11B
    EPwm11Regs.AQCTLB.bit.CBD = AQ_SET;

    // EPWM11B Negative
    //EPwm11Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM11B
    //EPwm11Regs.AQCTLB.bit.CBD = AQ_CLEAR;


    // Interrupt where we will change the Compare Values
    //
    //EPwm11Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;    // Select INT on Zero event
    EPwm11Regs.ETSEL.bit.INTSEL = ET_CTR_PRDZERO;  // (double update) Select INT on Zero and Period event
    EPwm11Regs.ETSEL.bit.INTEN = 1;                // Enable INT
    EPwm11Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
}
//
// InitEPwm12 - Initialize EPWM12 configuration
//
void InitEPwm12()
{
    // Set Clock
    EPwm12Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm12Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Set Compare values
    EPwm12Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm12Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    // Setup counter mode
    EPwm12Regs.TBCTR = 0x0000;                       // Clear counter
    EPwm12Regs.TBPRD = EPWMx_TMAX[11];                // Set Max Count

    EPwm12Regs.TBPHS.bit.TBPHS = EPWMx_PS[11];        // Phase Shift (initial counter value)
    EPwm12Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[11];   // Set Initial Count Direction
    EPwm12Regs.TBCTL.bit.PHSEN = TB_ENABLE;           // Enable phase loading   // Disable phase loading
    EPwm12Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up and down -- Symmetric PWM /\/\/\

    EPwm12Regs.TBCTL.bit.PRDLD = TB_SHADOW;          // Upload duty-cycle in the next sampling
    EPwm12Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // sync flow-through to sync EPWM7

    // Dead Time
    EPwm12Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;


    // Setup shadowing
    EPwm12Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm12Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm12Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD; // (Double Update) Load on Zero and Period
    EPwm12Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    // PWM Logic
    //************************
    // EPWM12A Positive
    EPwm12Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM12A
    EPwm12Regs.AQCTLA.bit.CAD = AQ_SET;

    // EPWM12B Positive
    EPwm12Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM12B
    EPwm12Regs.AQCTLB.bit.CBD = AQ_SET;

    // EPWM12B Negative
    //EPwm12Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM12B
    //EPwm12Regs.AQCTLB.bit.CBD = AQ_CLEAR;


    // Interrupt where we will change the Compare Values
    //
    //EPwm12Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;    // Select INT on Zero event
    EPwm12Regs.ETSEL.bit.INTSEL = ET_CTR_PRDZERO;  // (double update) Select INT on Zero and Period event
    EPwm12Regs.ETSEL.bit.INTEN = 1;                // Enable INT
    EPwm12Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
}
/* EPWM updates -- To change settings online
******************************************************************/
void UpdateEPwm1()
{
    unsigned int temp_DB = 0;
    EPwm1Regs.TBPRD = EPWMx_TMAX[0];                // algo es dependiente de este registro que no puede ser doble de freq
    EPWMx_PS_DEG[0] = 0;
    EPWMx_PS[0] = 0;
    EPWMx_PHSDIR[0] = 0;          // update dpuble update, change count direction
    EPwm1Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[0];   // Set Count Direction UP
    //if (EPWM_ALL_CMP == 1)
    if (EPWMx_COMP[0] == 1)
    {
        EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
        EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
        temp_DB = (unsigned int)(DB_Gain_ns*EPWMx_DB[0]);
        EPwm1Regs.DBFED.bit.DBFED = temp_DB;
        EPwm1Regs.DBRED.bit.DBRED = temp_DB;
    }
    else
        EPwm1Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;

}
void UpdateEPwm2()
{
    unsigned int temp_DB = 0;
    EPwm2Regs.TBPRD = EPWMx_TMAX[1];
    EPwm2Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[1];   // Set Count Direction
    EPwm2Regs.TBPHS.bit.TBPHS = EPWMx_PS[1];        // Set Phase Shift
    //if (EPWM_ALL_CMP == 1)
    if (EPWMx_COMP[1] == 1)
    {
        EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
        EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
        temp_DB = (unsigned int)(DB_Gain_ns*EPWMx_DB[1]);
        EPwm2Regs.DBFED.bit.DBFED = (unsigned int)(temp_DB);
        EPwm2Regs.DBRED.bit.DBRED = (unsigned int)(temp_DB);
    }
    else
        EPwm2Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
}
void UpdateEPwm3()
{
    unsigned int temp_DB = 0;
    EPwm3Regs.TBPRD = EPWMx_TMAX[2];
    EPwm3Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[2];    // Set Count Direction
    EPwm3Regs.TBPHS.bit.TBPHS = EPWMx_PS[2];        // Set Phase Shift
    //if (EPWM_ALL_CMP == 1)
    if (EPWMx_COMP[2] == 1)
    {
        EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
        EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
        temp_DB = (unsigned int)(DB_Gain_ns*EPWMx_DB[2]);
        EPwm3Regs.DBFED.bit.DBFED = (unsigned int)(temp_DB);
        EPwm3Regs.DBRED.bit.DBRED = (unsigned int)(temp_DB);
        }
    else
        EPwm3Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
}
void UpdateEPwm4()
{
    unsigned int temp_DB = 0;
    EPwm4Regs.TBPRD = EPWMx_TMAX[3];
    EPwm4Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[3];    // Set Count Direction
    EPwm4Regs.TBPHS.bit.TBPHS = EPWMx_PS[3];        // Set Phase Shift
    //if (EPWM_ALL_CMP == 1)
    if (EPWMx_COMP[3] == 1)
    {
        EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
        EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
        temp_DB = (unsigned int)(DB_Gain_ns*EPWMx_DB[3]);
        EPwm4Regs.DBFED.bit.DBFED = (unsigned int)(temp_DB);
        EPwm4Regs.DBRED.bit.DBRED = (unsigned int)(temp_DB);
    }
    else
        EPwm4Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
}
void UpdateEPwm5()
{
    unsigned int temp_DB = 0;
    EPwm5Regs.TBPRD = EPWMx_TMAX[4];
    EPwm5Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[4];    // Set Count Direction
    EPwm5Regs.TBPHS.bit.TBPHS = EPWMx_PS[4];        // Set Phase Shift
    //if (EPWM_ALL_CMP == 1)
    if (EPWMx_COMP[4] == 1)
    {
        EPwm5Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
        EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
        temp_DB = (unsigned int)(DB_Gain_ns*EPWMx_DB[4]);
        EPwm5Regs.DBFED.bit.DBFED = (unsigned int)(temp_DB);
        EPwm5Regs.DBRED.bit.DBRED = (unsigned int)(temp_DB);
    }
    else
        EPwm5Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
}
void UpdateEPwm6()
{
    unsigned int temp_DB = 0;
    EPwm6Regs.TBPRD = EPWMx_TMAX[5];
    EPwm6Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[5];    // Set Count Direction
    EPwm6Regs.TBPHS.bit.TBPHS = EPWMx_PS[5];        // Set Phase Shift
    //if (EPWM_ALL_CMP == 1)
    if (EPWMx_COMP[5] == 1)
    {
        EPwm6Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
        EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
        temp_DB = (unsigned int)(DB_Gain_ns*EPWMx_DB[5]);
        EPwm6Regs.DBFED.bit.DBFED = (unsigned int)(temp_DB);
        EPwm6Regs.DBRED.bit.DBRED = (unsigned int)(temp_DB);
    }
    else
        EPwm6Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
}
void UpdateEPwm7()
{
    unsigned int temp_DB = 0;
    EPwm7Regs.TBPRD = EPWMx_TMAX[6];
    EPwm7Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[6];    // Set Count Direction
    EPwm7Regs.TBPHS.bit.TBPHS = EPWMx_PS[6];        // Set Phase Shift
    //if (EPWM_ALL_CMP == 1)
    if (EPWMx_COMP[6] == 1)
    {
        EPwm7Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
        EPwm7Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
        temp_DB = (unsigned int)(DB_Gain_ns*EPWMx_DB[6]);
        EPwm7Regs.DBFED.bit.DBFED = (unsigned int)(temp_DB);
        EPwm7Regs.DBRED.bit.DBRED = (unsigned int)(temp_DB);
    }
    else
        EPwm7Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
}
void UpdateEPwm8()
{
    unsigned int temp_DB = 0;
    EPwm8Regs.TBPRD = EPWMx_TMAX[7];
    EPwm8Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[7];    // Set Count Direction
    EPwm8Regs.TBPHS.bit.TBPHS = EPWMx_PS[7];        // Set Phase Shift
    //if (EPWM_ALL_CMP == 1)
    if (EPWMx_COMP[7] == 1)
    {
        EPwm8Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
        EPwm8Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
        temp_DB = (unsigned int)(DB_Gain_ns*EPWMx_DB[7]);
        EPwm8Regs.DBFED.bit.DBFED = (unsigned int)(temp_DB);
        EPwm8Regs.DBRED.bit.DBRED = (unsigned int)(temp_DB);
    }
    else
        EPwm8Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
}
void UpdateEPwm9()
{
    unsigned int temp_DB = 0;
    EPwm9Regs.TBPRD = EPWMx_TMAX[8];
    EPwm9Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[8];    // Set Count Direction
    EPwm9Regs.TBPHS.bit.TBPHS = EPWMx_PS[8];        // Set Phase Shift
    //if (EPWM_ALL_CMP == 1)
    if (EPWMx_COMP[8] == 1)
    {
        EPwm9Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
        EPwm9Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
        temp_DB = (unsigned int)(DB_Gain_ns*EPWMx_DB[8]);
        EPwm9Regs.DBFED.bit.DBFED = (unsigned int)(temp_DB);
        EPwm9Regs.DBRED.bit.DBRED = (unsigned int)(temp_DB);
    }
    else
        EPwm9Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
}
void UpdateEPwm10()
{
    unsigned int temp_DB = 0;
    EPwm10Regs.TBPRD = EPWMx_TMAX[9];
    EPwm10Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[9];    // Set Count Direction
    EPwm10Regs.TBPHS.bit.TBPHS = EPWMx_PS[9];        // Set Phase Shift
    //if (EPWM_ALL_CMP == 1)
    if (EPWMx_COMP[9] == 1)
    {
        EPwm10Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
        EPwm10Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
        temp_DB = (unsigned int)(DB_Gain_ns*EPWMx_DB[9]);
        EPwm10Regs.DBFED.bit.DBFED = (unsigned int)(temp_DB);
        EPwm10Regs.DBRED.bit.DBRED = (unsigned int)(temp_DB);
    }
    else
        EPwm10Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
}
void UpdateEPwm11()
{
    unsigned int temp_DB = 0;
    EPwm11Regs.TBPRD = EPWMx_TMAX[10];
    EPwm11Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[10];    // Set Count Direction
    EPwm11Regs.TBPHS.bit.TBPHS = EPWMx_PS[10];        // Set Phase Shift
    //if (EPWM_ALL_CMP == 1)
    if (EPWMx_COMP[10] == 1)
    {
        EPwm11Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
        EPwm11Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
        temp_DB = (unsigned int)(DB_Gain_ns*EPWMx_DB[10]);
        EPwm11Regs.DBFED.bit.DBFED = (unsigned int)(temp_DB);
        EPwm11Regs.DBRED.bit.DBRED = (unsigned int)(temp_DB);
    }
    else
        EPwm11Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
}
void UpdateEPwm12()
{
    unsigned int temp_DB = 0;
    EPwm12Regs.TBPRD = EPWMx_TMAX[11];
    EPwm12Regs.TBCTL.bit.PHSDIR = EPWMx_PHSDIR[11];    // Set Count Direction
    EPwm12Regs.TBPHS.bit.TBPHS = EPWMx_PS[11];        // Set Phase Shift
    //if (EPWM_ALL_CMP == 1)
    if (EPWMx_COMP[11] == 1)
    {
        EPwm12Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
        EPwm12Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
        temp_DB = (unsigned int)(DB_Gain_ns*EPWMx_DB[11]);
        EPwm12Regs.DBFED.bit.DBFED = (unsigned int)(temp_DB);
        EPwm12Regs.DBRED.bit.DBRED = (unsigned int)(temp_DB);
    }
    else
        EPwm12Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
}

void UPDATE_ALL_EPWM_SYNC()
{
    
    /*
    if (update_Epwms==1)
    {
        //EPWM_ALL_SAME_FQ(EPWM_ALL_FQ);
        //EPWM_ALL_SAME_DB(EPWM_ALL_DB);

        if (ADC_Trigger == ET_CTR_PRDZERO)
            Ts = 1/(2*1000*EPWMx_FQ[ADC_EPWM-1]);
        else
            Ts = 1/(1000*EPWMx_FQ[ADC_EPWM-1]);
*/
        // carriers 1 must not be re-syncrhonized
        UpdateEPwm1();   // esta linea da problemas
        UpdateEPwm2();
        UpdateEPwm3();
        UpdateEPwm4();
        UpdateEPwm5();
        UpdateEPwm6();
        UpdateEPwm7();
        UpdateEPwm8();
        UpdateEPwm9();
        UpdateEPwm10();
        UpdateEPwm11();
        UpdateEPwm12();

  //      update_Epwms = 0;
   // }
}


void Inverting_PWMx_A(unsigned int pwm)
{
    if (pwm==1)
    {
        EPwm1Regs.AQCTLA.bit.CAU = AQ_SET; // set actions for EPWM1A
        EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    }
    if (pwm==2)
    {
        EPwm2Regs.AQCTLA.bit.CAU = AQ_SET; // set actions for EPWM2A
        EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    }
    if (pwm==3)
    {
        EPwm3Regs.AQCTLA.bit.CAU = AQ_SET; // set actions for EPWM3A
        EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    }
    if (pwm==4)
    {
        EPwm4Regs.AQCTLA.bit.CAU = AQ_SET; // set actions for EPWM4A
        EPwm4Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    }
    if (pwm==5)
    {
        EPwm5Regs.AQCTLA.bit.CAU = AQ_SET; // set actions for EPWM5A
        EPwm5Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    }
    if (pwm==6)
    {
        EPwm6Regs.AQCTLA.bit.CAU = AQ_SET; // set actions for EPWM6A
        EPwm6Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    }
    if (pwm==7)
    {
        EPwm7Regs.AQCTLA.bit.CAU = AQ_SET; // set actions for EPWM7A
        EPwm7Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    }
    if (pwm==8)
    {
        EPwm8Regs.AQCTLA.bit.CAU = AQ_SET; // set actions for EPWM8A
        EPwm8Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    }
    if (pwm==9)
    {
        EPwm9Regs.AQCTLA.bit.CAU = AQ_SET; // set actions for EPWM9A
        EPwm9Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    }
    if (pwm==10)
    {
        EPwm10Regs.AQCTLA.bit.CAU = AQ_SET; // set actions for EPWM10A
        EPwm10Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    }
    if (pwm==11)
    {
        EPwm11Regs.AQCTLA.bit.CAU = AQ_SET; // set actions for EPWM11A
        EPwm11Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    }
    if (pwm==12)
    {
        EPwm12Regs.AQCTLA.bit.CAU = AQ_SET; // set actions for EPWM12A
        EPwm12Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    }
}


void Noninverting_PWMx_A(unsigned int pwm)
{
    if (pwm==1)
    {
        EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM1A
        EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
    }
    if (pwm==2)
    {
        EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM2A
        EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;
    }
    if (pwm==3)
    {
        EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM3A
        EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;
    }
    if (pwm==4)
    {
        EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM4A
        EPwm4Regs.AQCTLA.bit.CAD = AQ_SET;
    }
    if (pwm==5)
    {
        EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM5A
        EPwm5Regs.AQCTLA.bit.CAD = AQ_SET;
    }
    if (pwm==6)
    {
        EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM6A
        EPwm6Regs.AQCTLA.bit.CAD = AQ_SET;
    }
    if (pwm==7)
    {
        EPwm7Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM7A
        EPwm7Regs.AQCTLA.bit.CAD = AQ_SET;
    }
    if (pwm==8)
    {
        EPwm8Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM8A
        EPwm8Regs.AQCTLA.bit.CAD = AQ_SET;
    }
    if (pwm==9)
    {
        EPwm9Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM9A
        EPwm9Regs.AQCTLA.bit.CAD = AQ_SET;
    }
    if (pwm==10)
    {
        EPwm10Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM10A
        EPwm10Regs.AQCTLA.bit.CAD = AQ_SET;
    }
    if (pwm==11)
    {
        EPwm11Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM11A
        EPwm11Regs.AQCTLA.bit.CAD = AQ_SET;
    }
    if (pwm==12)
    {
        EPwm12Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM12A
        EPwm12Regs.AQCTLA.bit.CAD = AQ_SET;
    }
}


void Inverting_PWMx_B(unsigned int pwm)
{
    if (pwm==1)
    {
        EPwm1Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM1B
        EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;
    }
    if (pwm==2)
    {
        EPwm2Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM2B
        EPwm2Regs.AQCTLB.bit.CBD = AQ_CLEAR;
    }
    if (pwm==3)
    {
        EPwm3Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM3B
        EPwm3Regs.AQCTLB.bit.CBD = AQ_CLEAR;
    }
    if (pwm==4)
    {
        EPwm4Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM4B
        EPwm4Regs.AQCTLB.bit.CBD = AQ_CLEAR;
    }
    if (pwm==5)
    {
        EPwm5Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM5B
        EPwm5Regs.AQCTLB.bit.CBD = AQ_CLEAR;
    }
    if (pwm==6)
    {
        EPwm6Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM6B
        EPwm6Regs.AQCTLB.bit.CBD = AQ_CLEAR;
    }
    if (pwm==7)
    {
        EPwm7Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM7B
        EPwm7Regs.AQCTLB.bit.CBD = AQ_CLEAR;
    }
    if (pwm==8)
    {
        EPwm8Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM8B
        EPwm8Regs.AQCTLB.bit.CBD = AQ_CLEAR;
    }
    if (pwm==9)
    {
        EPwm9Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM9B
        EPwm9Regs.AQCTLB.bit.CBD = AQ_CLEAR;
    }
    if (pwm==10)
    {
        EPwm10Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM10B
        EPwm10Regs.AQCTLB.bit.CBD = AQ_CLEAR;
    }
    if (pwm==11)
    {
        EPwm11Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM11B
        EPwm11Regs.AQCTLB.bit.CBD = AQ_CLEAR;
    }
    if (pwm==12)
    {
        EPwm12Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM12B
        EPwm12Regs.AQCTLB.bit.CBD = AQ_CLEAR;
    }
}


void Noninverting_PWMx_B(unsigned int pwm)
{
    if (pwm==1)
    {
        EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM1B
        EPwm1Regs.AQCTLB.bit.CBD = AQ_SET;
    }
    if (pwm==2)
    {
        EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM2B
        EPwm2Regs.AQCTLB.bit.CBD = AQ_SET;
    }
    if (pwm==3)
    {
        EPwm3Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM3B
        EPwm3Regs.AQCTLB.bit.CBD = AQ_SET;
    }
    if (pwm==4)
    {
        EPwm4Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM4B
        EPwm4Regs.AQCTLB.bit.CBD = AQ_SET;
    }
    if (pwm==5)
    {
        EPwm5Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM5B
        EPwm5Regs.AQCTLB.bit.CBD = AQ_SET;
    }
    if (pwm==6)
    {
        EPwm6Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM6B
        EPwm6Regs.AQCTLB.bit.CBD = AQ_SET;
    }
    if (pwm==7)
    {
        EPwm7Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM7B
        EPwm7Regs.AQCTLB.bit.CBD = AQ_SET;
    }
    if (pwm==8)
    {
        EPwm8Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM8B
        EPwm8Regs.AQCTLB.bit.CBD = AQ_SET;
    }
    if (pwm==9)
    {
        EPwm9Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM9B
        EPwm9Regs.AQCTLB.bit.CBD = AQ_SET;
    }
    if (pwm==10)
    {
        EPwm10Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM10B
        EPwm10Regs.AQCTLB.bit.CBD = AQ_SET;
    }
    if (pwm==11)
    {
        EPwm11Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM11B
        EPwm11Regs.AQCTLB.bit.CBD = AQ_SET;
    }
    if (pwm==12)
    {
        EPwm12Regs.AQCTLB.bit.CBU = AQ_CLEAR; // set actions for EPWM12B
        EPwm12Regs.AQCTLB.bit.CBD = AQ_SET;
    }
}

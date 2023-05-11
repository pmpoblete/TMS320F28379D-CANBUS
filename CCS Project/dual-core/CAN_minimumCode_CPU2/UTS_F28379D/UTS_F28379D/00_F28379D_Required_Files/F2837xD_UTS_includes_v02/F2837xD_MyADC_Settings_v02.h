

/* ADC Functions
******************************************************************/
void set_ADC_ePWM_SYNC(Uint16, Uint16);

void set_ADC_parallel_conv_ABCD(Uint16, Uint16, Uint16, Uint16);

extern void setup_ADC_A(void);
extern void setup_ADC_B(void);
extern void setup_ADC_C(void);
extern void setup_ADC_D(void);

void ConfigureADC_A(void);
void ConfigureADC_B(void);
void ConfigureADC_C(void);
void ConfigureADC_D(void);

extern Uint16 read_ADC_A(Uint16 ch);
extern Uint16 read_ADC_B(Uint16 ch);
extern Uint16 read_ADC_C(Uint16 ch);
extern Uint16 read_ADC_D(Uint16 ch);


extern void DelayUs(Uint16);

interrupt void adca1_isr(void);
void DT_Control_Loop(void);

/* My Functions
******************************************************************/

void set_ADC_parallel_conv_ABCD(Uint16 chA, Uint16 chB, Uint16 chC, Uint16 chD){
    ADC_A_ch_in[SOC_counter]=chA;
    ADC_B_ch_in[SOC_counter]=chB;
    ADC_C_ch_in[SOC_counter]=chC;
    ADC_D_ch_in[SOC_counter]=chD;
    SOC_counter++;
}

void set_ADC_ePWM_SYNC(Uint16 pwm, Uint16 ADC_Sampling)
{
    ADC_EPWM = pwm;
    
    if (ADC_Sampling == 0)
    {
        ADC_Trigger = ET_CTR_ZERO;      // Single-Update in Zero ETSEL (Event Trigger Select);
        Ts = 1/(1*1000*EPWMx_FQ[ADC_EPWM-1]);
    }
          
    if (ADC_Sampling == 1)
    {
        ADC_Trigger = ET_CTR_PRD;           // Single-Update in Max Ciunt ETSEL (Event Trigger Select);
        Ts = 1/(1*1000*EPWMx_FQ[ADC_EPWM-1]);
    }
        
    if (ADC_Sampling == 2)
    {
        ADC_Trigger = ET_CTR_PRDZERO;   // Double-Update (Zero and MAx Count) ETSEL (Event Trigger Select);
        Ts = 1/(2*1000*EPWMx_FQ[ADC_EPWM-1]);
    }
        

    switch (ADC_EPWM) {
    case 1:
        EPwm1Regs.ETSEL.bit.SOCAEN  = 1;            // Enable SOC on A group
        EPwm1Regs.ETSEL.bit.SOCASEL = ADC_Trigger;
        EPwm1Regs.ETPS.bit.SOCAPRD  = ET_1ST;       // Generate pulse on 1st event
        EPwm1Regs.ETSEL.bit.SOCBEN  = 1;            // Enable SOC on B group
        EPwm1Regs.ETSEL.bit.SOCBSEL = ADC_Trigger;
        EPwm1Regs.ETPS.bit.SOCBPRD  = ET_1ST;       // Generate pulse on 1st event
        break;
    case 2:
        EPwm2Regs.ETSEL.bit.SOCAEN  = 1;            // Enable SOC on A group
        EPwm2Regs.ETSEL.bit.SOCASEL = ADC_Trigger;
        EPwm2Regs.ETPS.bit.SOCAPRD  = ET_1ST;       // Generate pulse on 1st event
        EPwm2Regs.ETSEL.bit.SOCBEN  = 1;            // Enable SOC on B group
        EPwm2Regs.ETSEL.bit.SOCBSEL = ADC_Trigger;
        EPwm2Regs.ETPS.bit.SOCBPRD  = ET_1ST;       // Generate pulse on 1st event
        break;
    case 3:
        EPwm3Regs.ETSEL.bit.SOCAEN  = 1;            // Enable SOC on A group
        EPwm3Regs.ETSEL.bit.SOCASEL = ADC_Trigger;
        EPwm3Regs.ETPS.bit.SOCAPRD  = ET_1ST;       // Generate pulse on 1st event
        EPwm3Regs.ETSEL.bit.SOCBEN  = 1;            // Disable SOC on B group
        EPwm3Regs.ETSEL.bit.SOCBSEL = ADC_Trigger;
        EPwm3Regs.ETPS.bit.SOCBPRD  = ET_1ST;       // Generate pulse on 1st event
        break;
    case 4:
        EPwm4Regs.ETSEL.bit.SOCAEN  = 1;            // Enable SOC on A group
        EPwm4Regs.ETSEL.bit.SOCASEL = ADC_Trigger;
        EPwm4Regs.ETPS.bit.SOCAPRD  = ET_1ST;       // Generate pulse on 1st event
        EPwm4Regs.ETSEL.bit.SOCBEN  = 1;            // Enable SOC on A group
        EPwm4Regs.ETSEL.bit.SOCBSEL = ADC_Trigger;
        EPwm4Regs.ETPS.bit.SOCBPRD  = ET_1ST;       // Generate pulse on 1st event
        break;
    case 5:
        EPwm5Regs.ETSEL.bit.SOCAEN  = 1;            // Enable SOC on A group
        EPwm5Regs.ETSEL.bit.SOCASEL = ADC_Trigger;
        EPwm5Regs.ETPS.bit.SOCAPRD  = ET_1ST;       // Generate pulse on 1st event
        EPwm5Regs.ETSEL.bit.SOCBEN  = 1;            // Enable SOC on B group
        EPwm5Regs.ETSEL.bit.SOCBSEL = ADC_Trigger;
        EPwm5Regs.ETPS.bit.SOCBPRD  = ET_1ST;       // Generate pulse on 1st event
        break;
    case 6:
        EPwm6Regs.ETSEL.bit.SOCAEN  = 1;            // Enable SOC on A group
        EPwm6Regs.ETSEL.bit.SOCASEL = ADC_Trigger;
        EPwm6Regs.ETPS.bit.SOCAPRD  = ET_1ST;       // Generate pulse on 1st event
        EPwm6Regs.ETSEL.bit.SOCBEN  = 1;            // Enable SOC on B group
        EPwm6Regs.ETSEL.bit.SOCBSEL = ADC_Trigger;
        EPwm6Regs.ETPS.bit.SOCBPRD  = ET_1ST;       // Generate pulse on 1st event
        break;
    case 7:
        EPwm7Regs.ETSEL.bit.SOCAEN  = 1;            // Enable SOC on A group
        EPwm7Regs.ETSEL.bit.SOCASEL = ADC_Trigger;
        EPwm7Regs.ETPS.bit.SOCAPRD  = ET_1ST;       // Generate pulse on 1st event
        EPwm7Regs.ETSEL.bit.SOCBEN  = 1;            // Enable SOC on B group
        EPwm7Regs.ETSEL.bit.SOCBSEL = ADC_Trigger;
        EPwm7Regs.ETPS.bit.SOCBPRD  = ET_1ST;       // Generate pulse on 1st event
        break;
    case 8:
        EPwm8Regs.ETSEL.bit.SOCAEN  = 1;            // Enable SOC on A group
        EPwm8Regs.ETSEL.bit.SOCASEL = ADC_Trigger;
        EPwm8Regs.ETPS.bit.SOCAPRD  = ET_1ST;       // Generate pulse on 1st event
        EPwm8Regs.ETSEL.bit.SOCBEN  = 1;            // Enable SOC on B group
        EPwm8Regs.ETSEL.bit.SOCBSEL = ADC_Trigger;
        EPwm8Regs.ETPS.bit.SOCBPRD  = ET_1ST;       // Generate pulse on 1st event
        break;
    case 9:
        EPwm9Regs.ETSEL.bit.SOCAEN  = 1;            // Enable SOC on A group
        EPwm9Regs.ETSEL.bit.SOCASEL = ADC_Trigger;
        EPwm9Regs.ETPS.bit.SOCAPRD  = ET_1ST;       // Generate pulse on 1st event
        EPwm9Regs.ETSEL.bit.SOCBEN  = 1;            // Enable SOC on B group
        EPwm9Regs.ETSEL.bit.SOCBSEL = ADC_Trigger;
        EPwm9Regs.ETPS.bit.SOCBPRD  = ET_1ST;       // Generate pulse on 1st event
        break;
    case 10:
        EPwm10Regs.ETSEL.bit.SOCAEN  = 1;           // Enable SOC on A group
        EPwm10Regs.ETSEL.bit.SOCASEL = ADC_Trigger;
        EPwm10Regs.ETPS.bit.SOCAPRD  = ET_1ST;      // Generate pulse on 1st event
        EPwm10Regs.ETSEL.bit.SOCBEN  = 1;           // Enable SOC on B group
        EPwm10Regs.ETSEL.bit.SOCBSEL = ADC_Trigger;
        EPwm10Regs.ETPS.bit.SOCBPRD  = ET_1ST;      // Generate pulse on 1st event
        break;
    case 11:
        EPwm11Regs.ETSEL.bit.SOCAEN  = 1;           // Enable SOC on A group
        EPwm11Regs.ETSEL.bit.SOCASEL = ADC_Trigger;
        EPwm11Regs.ETPS.bit.SOCAPRD  = ET_1ST;      // Generate pulse on 1st event
        EPwm11Regs.ETSEL.bit.SOCBEN  = 1;           // Enable SOC on B group
        EPwm11Regs.ETSEL.bit.SOCBSEL = ADC_Trigger;
        EPwm11Regs.ETPS.bit.SOCBPRD  = ET_1ST;      // Generate pulse on 1st event
        break;
    case 12:
        EPwm12Regs.ETSEL.bit.SOCAEN  = 1;           // Disable SOC on A group
        EPwm12Regs.ETSEL.bit.SOCASEL = ADC_Trigger;
        EPwm12Regs.ETPS.bit.SOCAPRD  = ET_1ST;      // Generate pulse on 1st event
        EPwm12Regs.ETSEL.bit.SOCBEN  = 1;           // Disable SOC on B group
        EPwm12Regs.ETSEL.bit.SOCBSEL = ADC_Trigger;
        EPwm12Regs.ETPS.bit.SOCBPRD  = ET_1ST;      // Generate pulse on 1st event
        break;
    }
//End of ADC_EPWM_SYNC
}


void ConfigureADC_A(void)
{
    EALLOW;
    //--- Reset the ADC.  This is good programming practice.
    DevCfgRegs.SOFTPRES13.bit.ADC_A = 1;    // ADC is reset
    DevCfgRegs.SOFTPRES13.bit.ADC_A = 0;    // ADC is released from reset
    
    //write configurations
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    //AdcaRegs.ADCCTL2.bit.PRESCALE = 0; //set ADCCLK divider to /1
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    
    //Set pulse positions to late
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    
    //power up the ADC
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    
    //delay for 1ms to allow ADC time to power up
    DelayUs(1000);

    PieVectTable.ADCA1_INT = &adca1_isr; //function for ADCA interrupt 1

    IER |= M_INT1; //Enable group 1 interrupts for ADC

    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;  //ADC

    EDIS;
}

void ConfigureADC_C(void)
{
    EALLOW;
    //--- Reset the ADC.  This is good programming practice.
    DevCfgRegs.SOFTPRES13.bit.ADC_C = 1;    // ADC is reset
    DevCfgRegs.SOFTPRES13.bit.ADC_C = 0;    // ADC is released from reset

    //write configurations
    AdccRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    //AdccRegs.ADCCTL2.bit.PRESCALE = 0;//set ADCCLK divider to /1: nosier measurement
    AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    //Set pulse positions to late
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    //power up the ADC
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    //delay for 1ms to allow ADC time to power up
    DelayUs(1000);

    EDIS;
}



void ConfigureADC_B(void)
{
    EALLOW;
    //--- Reset the ADC.  This is good programming practice.
    DevCfgRegs.SOFTPRES13.bit.ADC_B = 1;    // ADC is reset
    DevCfgRegs.SOFTPRES13.bit.ADC_B = 0;    // ADC is released from reset

    //write configurations
    AdcbRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    //AdcbRegs.ADCCTL2.bit.PRESCALE = 0; // set ADCCLK divider to /1: nosier measurement
    AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    //Set pulse positions to late
    AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    //power up the ADC
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    //delay for 1ms to allow ADC time to power up
    DelayUs(1000);

    EDIS;
}

void ConfigureADC_D(void)
{
    EALLOW;
    //--- Reset the ADC.  This is good programming practice.
    DevCfgRegs.SOFTPRES13.bit.ADC_D = 1;    // ADC is reset
    DevCfgRegs.SOFTPRES13.bit.ADC_D = 0;    // ADC is released from reset

    //write configurations
    AdcdRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    //AdcdRegs.ADCCTL2.bit.PRESCALE = 0; //set ADCCLK divider to /1: nosier measurement
    AdcSetMode(ADC_ADCD, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    //Set pulse positions to late
    AdcdRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    //power up the ADC
    AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    //delay for 1ms to allow ADC time to power up
    DelayUs(1000);

    EDIS;
}






void setup_ADC_A(void)
{
    ConfigureADC_A();

    Uint16 acqps=19;

    // Determine minimum acquisition window (in SYSCLKS) based on resolution
    if(ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION)
    {
        //Min adquisition time is 75ns
        //acqps = 14; //75ns
        acqps = 19; //(19+1)/200MHz = 100ns. The min is 75ns

    }
    else //resolution is 16-bit
    {
        acqps = 63; //320ns  ((63+1)*(1/200MHz))
    }

    //Select the channels to convert and end of conversion flag
    //
    EALLOW;
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = ADC_A_ch_in[0];  //SOC0 will convert pin A0
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 3+2*ADC_EPWM; //trigger on ePWMx SOCA
                                                   //  5: ePWM1 for SOCA
                                                   //  7: ePWM2 for SOCA
                                                   //  9: ePWM3 for SOCA
                                                   // ...
                                                   // 27: ePWM12 for SOCA

    AdcaRegs.ADCSOC1CTL.bit.CHSEL = ADC_A_ch_in[1];  //SOC0 will convert pin A0
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 3+2*ADC_EPWM; //trigger on ePWMx SOCA

    AdcaRegs.ADCSOC2CTL.bit.CHSEL = ADC_A_ch_in[2];  //SOC0 will convert pin A0
    AdcaRegs.ADCSOC2CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 3+2*ADC_EPWM; //trigger on ePWMx SOCA

    AdcaRegs.ADCSOC3CTL.bit.CHSEL = ADC_A_ch_in[3];  //SOC0 will convert pin A0
    AdcaRegs.ADCSOC3CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = 3+2*ADC_EPWM; //trigger on ePWMx SOCA

    AdcaRegs.ADCSOC4CTL.bit.CHSEL = ADC_A_ch_in[4];  //SOC0 will convert pin A0
    AdcaRegs.ADCSOC4CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = 3+2*ADC_EPWM; //trigger on ePWMx SOCA

    AdcaRegs.ADCSOC5CTL.bit.CHSEL = ADC_A_ch_in[5];  //SOC0 will convert pin A0
    AdcaRegs.ADCSOC5CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC5CTL.bit.TRIGSEL = 3+2*ADC_EPWM; //trigger on ePWMx SOCA

    SOC_EOC = SOC_counter-1;
    if (SOC_EOC>5)
        SOC_EOC=5;


    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = SOC_EOC; //end of SOCx will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;   //enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared
    EDIS;
}

void setup_ADC_C(void)
{
    ConfigureADC_C();

    Uint16 acqps=19;

    // Determine minimum acquisition window (in SYSCLKS) based on resolution
    if(ADC_RESOLUTION_12BIT == AdccRegs.ADCCTL2.bit.RESOLUTION)
    {
        //Min adquisition time is 75ns
        //acqps = 14; //75ns
        acqps = 19; //(19+1)/200MHz = 100ns. The min is 75ns

    }
    else //resolution is 16-bit
    {
        acqps = 63; //320ns  ((63+1)*(1/200MHz))
    }

    //Select the channels to convert and end of conversion flag
    //
    EALLOW;
    AdccRegs.ADCSOC0CTL.bit.CHSEL = ADC_C_ch_in[0];  //SOC0 will convert pin A0
    AdccRegs.ADCSOC0CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 3+2*ADC_EPWM; //trigger on ePWMx SOCA
                                                   //  5: ePWM1 for SOCA
                                                   //  7: ePWM2 for SOCA
                                                   //  9: ePWM3 for SOCA
                                                   // ...
                                                   // 27: ePWM12 for SOCA

    AdccRegs.ADCSOC1CTL.bit.CHSEL = ADC_C_ch_in[1];  //SOC1 will convert pin A0
    AdccRegs.ADCSOC1CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC1CTL.bit.TRIGSEL = 3+2*ADC_EPWM; //trigger on ePWMx SOCA

    AdccRegs.ADCSOC2CTL.bit.CHSEL = ADC_C_ch_in[2];  //SOC2 will convert pin A0
    AdccRegs.ADCSOC2CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC2CTL.bit.TRIGSEL = 3+2*ADC_EPWM; //trigger on ePWMx SOCA

    AdccRegs.ADCSOC3CTL.bit.CHSEL = ADC_C_ch_in[3];  //SOC3 will convert pin A0
    AdccRegs.ADCSOC3CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC3CTL.bit.TRIGSEL = 3+2*ADC_EPWM; //trigger on ePWMx SOCA

    AdccRegs.ADCSOC4CTL.bit.CHSEL = ADC_C_ch_in[4];  //SOC3 will convert pin A0
    AdccRegs.ADCSOC4CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC4CTL.bit.TRIGSEL = 3+2*ADC_EPWM; //trigger on ePWMx SOCA

    AdccRegs.ADCSOC5CTL.bit.CHSEL = ADC_C_ch_in[5];  //SOC3 will convert pin A0
    AdccRegs.ADCSOC5CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC5CTL.bit.TRIGSEL = 3+2*ADC_EPWM; //trigger on ePWMx SOCA

    EDIS;
}


void setup_ADC_B(void)
{
    ConfigureADC_B();

    Uint16 acqps=19;

    // Determine minimum acquisition window (in SYSCLKS) based on resolution
    if(ADC_RESOLUTION_12BIT == AdcbRegs.ADCCTL2.bit.RESOLUTION)
    {
        //Min adquisition time is 75ns
        //acqps = 14; //75ns
        acqps = 19; //(19+1)/200MHz = 100ns. The min is 75ns

    }
    else //resolution is 16-bit
    {
        acqps = 63; //320ns  ((63+1)*(1/200MHz))
    }

    //Select the channels to convert and end of conversion flag
    //
    EALLOW;
    AdcbRegs.ADCSOC0CTL.bit.CHSEL = ADC_B_ch_in[0];  //SOC0 will convert pin A0
    AdcbRegs.ADCSOC0CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = 4+2*ADC_EPWM; //trigger on ePWMx SOCB
                                                   //  6: ePWM1 for SOCB
                                                   //  8: ePWM2 for SOCB
                                                   // 10: ePWM3 for SOCB
                                                   // ...
                                                   // 28: ePWM12 for SOCB

    AdcbRegs.ADCSOC1CTL.bit.CHSEL = ADC_B_ch_in[1];  //SOC1 will convert pin A0
    AdcbRegs.ADCSOC1CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC1CTL.bit.TRIGSEL = 4+2*ADC_EPWM; //trigger on ePWMx SOCB

    AdcbRegs.ADCSOC2CTL.bit.CHSEL = ADC_B_ch_in[2];  //SOC2 will convert pin A0
    AdcbRegs.ADCSOC2CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC2CTL.bit.TRIGSEL = 4+2*ADC_EPWM; //trigger on ePWMx SOCB

    AdcbRegs.ADCSOC3CTL.bit.CHSEL = ADC_B_ch_in[3];  //SOC3 will convert pin A0
    AdcbRegs.ADCSOC3CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC3CTL.bit.TRIGSEL = 4+2*ADC_EPWM; //trigger on ePWMx SOCB

    AdcbRegs.ADCSOC4CTL.bit.CHSEL = ADC_B_ch_in[4];  //SOC4 will convert pin A0
    AdcbRegs.ADCSOC4CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC4CTL.bit.TRIGSEL = 4+2*ADC_EPWM; //trigger on ePWMx SOCB

    AdcbRegs.ADCSOC5CTL.bit.CHSEL = ADC_B_ch_in[5];  //SOC2 will convert pin A0
    AdcbRegs.ADCSOC5CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC5CTL.bit.TRIGSEL = 4+2*ADC_EPWM; //trigger on ePWMx SOCB

    EDIS;
}

void setup_ADC_D(void)
{
    ConfigureADC_D();

    Uint16 acqps=19;

    // Determine minimum acquisition window (in SYSCLKS) based on resolution
    if(ADC_RESOLUTION_12BIT == AdcbRegs.ADCCTL2.bit.RESOLUTION)
    {
        //Min adquisition time is 75ns
        //acqps = 14; //75ns
        acqps = 19; //(19+1)/200MHz = 100ns. The min is 75ns

    }
    else //resolution is 16-bit
    {
        acqps = 63; //320ns  ((63+1)*(1/200MHz))
    }

    //Select the channels to convert and end of conversion flag
    //
    EALLOW;
    AdcdRegs.ADCSOC0CTL.bit.CHSEL = ADC_D_ch_in[0];  //SOC0 will convert pin A0
    AdcdRegs.ADCSOC0CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC0CTL.bit.TRIGSEL = 4+2*ADC_EPWM; //trigger on ePWMx SOCB
                                                   //  6: ePWM1 for SOCB
                                                   //  8: ePWM2 for SOCB
                                                   // 10: ePWM3 for SOCB
                                                   // ...
                                                   // 28: ePWM12 for SOCB

    AdcdRegs.ADCSOC1CTL.bit.CHSEL = ADC_D_ch_in[1];  //SOC0 will convert pin A0
    AdcdRegs.ADCSOC1CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC1CTL.bit.TRIGSEL = 4+2*ADC_EPWM; //trigger on ePWMx SOCB

    AdcdRegs.ADCSOC2CTL.bit.CHSEL = ADC_D_ch_in[2];  //SOC0 will convert pin A0
    AdcdRegs.ADCSOC2CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC2CTL.bit.TRIGSEL = 4+2*ADC_EPWM; //trigger on ePWMx SOCB

    AdcdRegs.ADCSOC3CTL.bit.CHSEL = ADC_D_ch_in[3];  //SOC0 will convert pin A0
    AdcdRegs.ADCSOC3CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC3CTL.bit.TRIGSEL = 4+2*ADC_EPWM; //trigger on ePWMx SOCB

    AdcdRegs.ADCSOC4CTL.bit.CHSEL = ADC_D_ch_in[4];  //SOC0 will convert pin A0
    AdcdRegs.ADCSOC4CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC4CTL.bit.TRIGSEL = 4+2*ADC_EPWM; //trigger on ePWMx SOCB

    AdcdRegs.ADCSOC5CTL.bit.CHSEL = ADC_D_ch_in[5];  //SOC0 will convert pin A0
    AdcdRegs.ADCSOC5CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC5CTL.bit.TRIGSEL = 4+2*ADC_EPWM; //trigger on ePWMx SOCB

    EDIS;
}


Uint16 read_ADC_A(Uint16 ch){
    Uint16 in_adc=0;
    if (ch<15)
        in_adc=ADC_A_input[ch];
    return in_adc;
}

Uint16 read_ADC_B(Uint16 ch){
    Uint16 in_adc=0;
    if (ch<15)
        in_adc=ADC_B_input[ch];
    return in_adc;
}

Uint16 read_ADC_C(Uint16 ch){
    Uint16 in_adc=0;
    if (ch<15)
        in_adc=ADC_C_input[ch];
    return in_adc;
}

Uint16 read_ADC_D(Uint16 ch){
    Uint16 in_adc=0;
    if (ch<15)
        in_adc=ADC_D_input[ch];
    return in_adc;
}

//
// adca1_isr - Read ADC Buffer in ISR
//

interrupt void adca1_isr(void)
{
    Uint16 i;

    i=ADC_A_ch_in[0];
    ADC_A_input[i]=AdcaResultRegs.ADCRESULT0;
    i=ADC_B_ch_in[0];
    ADC_B_input[i]=AdcbResultRegs.ADCRESULT0;
    i=ADC_C_ch_in[0];
    ADC_C_input[i]=AdccResultRegs.ADCRESULT0;
    i=ADC_D_ch_in[0];
    ADC_D_input[i]=AdcdResultRegs.ADCRESULT0;

    i=ADC_A_ch_in[1];
    ADC_A_input[i]=AdcaResultRegs.ADCRESULT1;
    i=ADC_B_ch_in[1];
    ADC_B_input[i]=AdcbResultRegs.ADCRESULT1;
    i=ADC_C_ch_in[1];
    ADC_C_input[i]=AdccResultRegs.ADCRESULT1;
    i=ADC_D_ch_in[1];
    ADC_D_input[i]=AdcdResultRegs.ADCRESULT1;

    i=ADC_A_ch_in[2];
    ADC_A_input[i]=AdcaResultRegs.ADCRESULT2;
    i=ADC_B_ch_in[2];
    ADC_B_input[i]=AdcbResultRegs.ADCRESULT2;
    i=ADC_C_ch_in[2];
    ADC_C_input[i]=AdccResultRegs.ADCRESULT2;
    i=ADC_D_ch_in[2];
    ADC_D_input[i]=AdcdResultRegs.ADCRESULT2;

    i=ADC_A_ch_in[3];
    ADC_A_input[i]=AdcaResultRegs.ADCRESULT3;
    i=ADC_B_ch_in[3];
    ADC_B_input[i]=AdcbResultRegs.ADCRESULT3;
    i=ADC_C_ch_in[3];
    ADC_C_input[i]=AdccResultRegs.ADCRESULT3;
    i=ADC_D_ch_in[3];
    ADC_D_input[i]=AdcdResultRegs.ADCRESULT3;

    i=ADC_A_ch_in[4];
    ADC_A_input[i]=AdcaResultRegs.ADCRESULT4;
    i=ADC_B_ch_in[4];
    ADC_B_input[i]=AdcbResultRegs.ADCRESULT4;
    i=ADC_C_ch_in[4];
    ADC_C_input[i]=AdccResultRegs.ADCRESULT4;
    i=ADC_D_ch_in[4];
    ADC_D_input[i]=AdcdResultRegs.ADCRESULT4;

    i=ADC_A_ch_in[5];
    ADC_A_input[i]=AdcaResultRegs.ADCRESULT5;
    i=ADC_B_ch_in[5];
    ADC_B_input[i]=AdcbResultRegs.ADCRESULT5;
    i=ADC_C_ch_in[5];
    ADC_C_input[i]=AdccResultRegs.ADCRESULT5;
    i=ADC_D_ch_in[5];
    ADC_D_input[i]=AdcdResultRegs.ADCRESULT5;


    DT_Control_Loop();

    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag

    // Check if overflow has occurred
    if(1 == AdcaRegs.ADCINTOVF.bit.ADCINT1)
    {
        AdcaRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
        AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


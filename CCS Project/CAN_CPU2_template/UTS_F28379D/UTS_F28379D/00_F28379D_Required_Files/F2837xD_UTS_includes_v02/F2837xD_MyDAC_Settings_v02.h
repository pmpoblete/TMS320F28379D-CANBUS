
/* DAC Functions
******************************************************************/

void set_DAC_A(void);
void write_DACA_pu(float);
void set_DAC_B(void);
void write_DACB_pu(float);



/* My Functions
******************************************************************/
void set_DAC_A()
{
    EALLOW; // This is needed to write to EALLOW protected registers

    //--- Configure DAC-B control registers
    DacaRegs.DACCTL.all = 0x0001;
    // bit 15-8      0's:    reserved
    // bit 7-4    0000:      DAC PWMSYNC select, not used since LOADMODE=0
    // bit 3         0:      reserved
    // bit 2         0:      LOADMODE, DACVALA load mode, 0=next SYSCLK, 1=next PWMSYNC specified by SYNCSEL
    // bit 1         0:      reserved
    // bit 0         1:      DACREFSEL, DAC reference select, 0=VDAC/VSSA, 1=ADC VREFHI/VREFLO

    //--- Set DAC-B output to mid-range
    DacaRegs.DACVALS.all = 0x0800;         // DACVALS = bits 11-0, bits 15-12 reserved

    //--- Enable DAC-B output
    DacaRegs.DACOUTEN.bit.DACOUTEN = 1;    // DAC output enable, 0=disable, 1=enable

    //--- DAC-B lock control register
    DacaRegs.DACLOCK.all = 0x0000;         // Write a 1 to lock (cannot be cleared once set)

    EDIS;   // This is needed to disable write to EALLOW protected registers


}

void write_DACA_pu(float out)
{
    if (out<0)
        out = 0;
    if (out>1)
        out = 1;
    if (Board_Type==1)
        out=1-out;

    DacaRegs.DACVALS.all = (unsigned int)(out*4095) ;
}

void set_DAC_B()
{
    EALLOW; // This is needed to write to EALLOW protected registers

    //--- Configure DAC-B control registers
    DacbRegs.DACCTL.all = 0x0001;
    // bit 15-8      0's:    reserved
    // bit 7-4    0000:      DAC PWMSYNC select, not used since LOADMODE=0
    // bit 3         0:      reserved
    // bit 2         0:      LOADMODE, DACVALA load mode, 0=next SYSCLK, 1=next PWMSYNC specified by SYNCSEL
    // bit 1         0:      reserved
    // bit 0         1:      DACREFSEL, DAC reference select, 0=VDAC/VSSA, 1=ADC VREFHI/VREFLO

    //--- Set DAC-B output to mid-range
    DacbRegs.DACVALS.all = 0x0800;         // DACVALS = bits 11-0, bits 15-12 reserved

    //--- Enable DAC-B output
    DacbRegs.DACOUTEN.bit.DACOUTEN = 1;    // DAC output enable, 0=disable, 1=enable

    //--- DAC-B lock control register
    DacbRegs.DACLOCK.all = 0x0000;         // Write a 1 to lock (cannot be cleared once set)

    EDIS;   // This is needed to disable write to EALLOW protected registers


}

void write_DACB_pu(float out)
{
    if (out<0)
        out = 0;
    if (out>1)
        out = 1;
    if (Board_Type==1)
        out=1-out;

    DacbRegs.DACVALS.all = (unsigned int)(out*4095) ;
}


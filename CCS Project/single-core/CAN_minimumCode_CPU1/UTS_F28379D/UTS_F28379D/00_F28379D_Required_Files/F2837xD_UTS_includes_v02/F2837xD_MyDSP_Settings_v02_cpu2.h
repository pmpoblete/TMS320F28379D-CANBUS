//
// Included Files
//
#include "F28x_Project.h"
#include "math.h"

/* Functions
******************************************************************/
extern void DSP_Setup(void);
void BOARD_LAUNCHXL(void);
void BOARD_controlCARD(void);
void Start_DSP(void);

extern void setup_ADC_A(void);
extern void setup_ADC_B(void);
extern void setup_ADC_C(void);
extern void setup_ADC_D(void);

void UPDATE_ALL_EPWM_SYNC(void);


void BOARD_LAUNCHXL(){
    InitSysPll(XTAL_OSC, IMULT_40, FMULT_0, PLLCLK_BY_2);
    Board_Type = 0;
}

void BOARD_controlCARD(){
    InitSysPll(XTAL_OSC, IMULT_20, FMULT_0, PLLCLK_BY_2);
    Board_Type = 1;
}

void Start_DSP(){

    //Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This function is found in the F2837xD_SysCtrl.c file./]
    InitSysCtrl();

    // Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    DINT;

    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the F2837xD_PieCtrl.c file.
    InitPieCtrl();

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in F2837xD_DefaultIsr.c.
    // This function is found in F2837xD_PieVect.c.
    InitPieVectTable();

    DSP_Setup();

    EALLOW;
    GpioCtrlRegs.GPCPUD.bit.GPIO73 = 0; // Enable pullup on GPIO73
    GpioCtrlRegs.GPCMUX1.bit.GPIO73 = 3; // GPIO73 = XCLKOUT(0)
    GpioCtrlRegs.GPCDIR.bit.GPIO73 = 1; // GPIO73 OUTPUT
    EDIS;

    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

}





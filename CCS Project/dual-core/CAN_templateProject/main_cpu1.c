//###########################################################################
//
// FILE:   main.c
//
// TITLE:  CAN basic for dual core operation
//
//
//! Template Developed by:
//! Dr Ricardo Aguilera and Pablo Poblete
//! University of Technology Sydney, Australia
//! pmpoblete@ieee.org
//!
//!
//###########################################################################


// Included Files for general purpose
#include "F28x_Project.h"
#include "math.h"

// Add folder F2837xD_UTS_includes_v02 in Include Options
#include "F2837xD_MyVars_Settings_v02.h"
#include "F2837xD_MyDSP_Settings_v02.h"
#include "F2837xD_MyEPwm_Settings_v02.h"
#include "F2837xD_MyADC_Settings_v02.h"
#include "F2837xD_MyDAC_Settings_v02.h"
#include "F2837xD_MyIO_Settings_v02.h"
#include "F2837xD_MyUART_Settings_v02.h"


// Global Variables
//********
#define FC_KHZ             1    // sampling frequency
#define MSG_DATA_LENGTH    8

unsigned int aux1 = 0;
unsigned int aux2 = 0;


// Function Prototypes
void DSP_Setup(void);
void DT_Control_Loop(void);


// Main Loop
//********
void main(void)
{
    Start_DSP();    // register init

    for(;;)
    {
        asm ("    NOP");
    }
}



// DSP Settings
//********
void DSP_Setup()
{
    BOARD_LAUNCHXL();

    // LED
    GPIO_Mode(31, OUTPUT);

    // set carrier frequency
    set_ALL_ePWMs_SYMM_kHz(1*FC_KHZ);  // All 24 PWMs with the same frequency

    // Set ADCs -- One channel per ADC_x (only 4 conversions, one per x module)
    //_________________________________________________________________

    //Options: SingleUpdate_Zero
    //         SingleUpdate_Max
    //         DoubleUpdate
    //set_ADC_ePWM_SYNC(1, SingleUpdate_Zero);  // sync with PWM 7
    EPWM_IND(11,1*FC_KHZ);
    set_ADC_ePWM_SYNC(11, DoubleUpdate);


    // CAN Port
    //_________________________________________________________________
    // Initialize GPIO:
    GPIO_SetupPinOptions(17, GPIO_INPUT, GPIO_ASYNC);
    GPIO_SetupPinOptions(12, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(17, GPIO_MUX_CPU2, 2);  //GPIO17 - CANRXB
    GPIO_SetupPinMux(12, GPIO_MUX_CPU2, 2);  //GPIO12 - CANTXB

    // red LED
    GPIO_SetupPinOptions(34, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(34, GPIO_MUX_CPU2, 0);

    EALLOW;
    DevCfgRegs.CPUSEL8.bit.CAN_B = 1;
    EDIS;
}



// Discrete-Time Control Loop
//********
void DT_Control_Loop(void){

    // _________Blink LED___________________
    aux1 += 1;
    if (aux1 >= FC_KHZ*1000)
    {
        aux2 = 1 - aux2;
        GPIO_WritePin(31, aux2);
        aux1 = 0;
    }
    //_____________________________

    // End Discrete-Time Control Loop
}

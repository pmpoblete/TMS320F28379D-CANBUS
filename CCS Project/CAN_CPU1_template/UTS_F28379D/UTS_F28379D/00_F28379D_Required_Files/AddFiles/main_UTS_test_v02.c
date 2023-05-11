//###########################################################################
//
// FILE:   main_UTS_test_v02.c
//
// TITLE:  Based code to develop discrete-time controllers for Power Converters
//
// In this example:
// ALL ePWMs symmetric (UP_Down)
// All ePWMs are firstly set to run at 10kHz
// All ePWMs are complementary with dead-time = 500 ns
//
// ADC_A interrupt triggered by ePWM1 Double Update (9kHz)
//
//! Developed by:
//! Dr Ricardo P. Aguilera
//! University of Technology Sydney, Australia
//! raguilera@ieee.org
//!
//! July 2020
//!
//
//###########################################################################

// Included Files
//
#include "F28x_Project.h"
#include "math.h"

// Add folder F2837xD_UTS_includes_v02 in Include Options
#include "F2837xD_MyVars_Settings_v02.h"
#include "F2837xD_MyDSP_Settings_v02.h"
#include "F2837xD_MyEPwm_Settings_v02.h"
#include "F2837xD_MyADC_Settings_v02.h"
#include "F2837xD_MyDAC_Settings_v02.h"
#include "F2837xD_MyIO_Settings_v02.h"

// Global Variables
//********************
#define PI      3.141592653589793
#define TWO_PI  6.283185307179586

float d = 0;
float d_constant = 0.5;
float d_adc = 0;
float m = 0.5;
float tetha = 0;

Uint16 constant_duty_cycle = 0;

// DSP Settings
//********************
void DSP_Setup(){

    /* 1. Select Board
    _______________________________________________________________________*/
    BOARD_LAUNCHXL();
    //BOARD_controlCARD();

    /* 2. Set EPWMs
    _______________________________________________________________________*/
    // Create 12 Independent Symmetric Synchronized PWMs  /\/\/\/\/\/
    // from EPM1A to EPWM6A and from EPM1B to EPWM6B
    // set_ALL_ePWMs_SYMM_kHz(x); where x is freq in kHz

    set_ALL_ePWMs_SYMM_kHz(10);  // All 24 PWMs with the same frequency

    // Reduce to 6 Complementary Symmetric Synchronized PWMs
    // from EPM1 to EPWM6 -->  EPWxA = NOT(EPWMxB)
    // set_ALL_ePWMs_SYMM_COMP(x); where x is dead-time in nano sec.

    set_ALL_ePWMs_SYMM_COMP(500); //add dead-time in ns



    // 3. Set ADCs -- One channel per ADC_x (only 4 conversions, one per x module)
    //_________________________________________________________________

    set_ADC_ePWM_SYNC(1, SingleUpdate_Zero); //Options: SingleUpdate_Zero
                                             //         SingleUpdate_Max
                                             //         DoubleUpdate

    //Set ADC parallel conversions (A,B,C,D)

    set_ADC_parallel_conv_ABCD(4,4,4,3);    //ADCINA4, ADCINB4, ADCINC4, ADCIND3 at the same time
    //set_ADC_parallel_conv_ABCD(5,5,5,1);    //ADCINA5, ADCINB5, ADCINC5, ADCIND1 at the same time

    // 4. Set DACs
    //_________________________________________________________________

    set_DAC_B();     //DAC DACOUTB       J7 pin70 in BOARD_LAUNCHXL

    // 5. Set General Purpose IOs  (16 to 28)
    //_________________________________________________________________

    GPIO_Mode(16,OUTPUT);

}

// Discrete-Time Control Loop
//********************
void DT_Control_Loop(void){
    // This loop is executed every Ts=1/fpwm6
    // Ts is available as global variable

    // GPIO 16 set to HIGH to start measuring calculation time
    GPIO_WritePin(16, HIGH);

    //Read ADCs
    Uint16 adc_in = 0;    //local integer variable to read ADC data

    //Read integer data from ADC_A channel x ADC_A(x)
    adc_in = read_ADC_A(4);
    //Read integer data from ADC_B channel x ADC_B(x)
    adc_in = read_ADC_B(4);
    //Read integer data from ADC_C channel x ADC_C(x)
    adc_in = read_ADC_C(4);
    //Read integer data from ADC_D channel x ADC_D(x)
    adc_in = read_ADC_D(3);

    // Transform integer into floating
    d_adc=(float)(0.0002442002442*adc_in);


    // create sinusoidal duty-cycle reference centered in 0.5
    d = m*0.5*sinf(tetha)+0.5;
    tetha += TWO_PI*50*Ts;  //theta(k+1)=theta(k)+2*pi*f*Ts
    if (tetha>TWO_PI)
        tetha=tetha-TWO_PI; //keep theta \in [0, 2pi]

    // Send duty-cycle reference to the DAC_B
    write_DACB_pu(d);

    // Use this to impose a constant duty-cycle
    if (constant_duty_cycle==1)
        d=d_constant;

    // Write ePWMxA duty-cycles on ePMs
    write_ePWMxA(1,d);
    write_ePWMxA(2,0.5);
    write_ePWMxA(3,d);

    // Write ePWMxB duty-cycles on ePMs
    // If using complementary EPMs then, duty-cycles are forced to be equal ePWMxB=ePWMxA
    write_ePWMxB(1,1-d);
    write_ePWMxB(2,1-d);
    write_ePWMxB(3,1-d);


    // Pin 16 set to LOW to finalize measuring calculation time
    GPIO_WritePin(16, LOW);

// End Discrete-Time Control Loop
}


// Main Loop
// DO NOT CHANGE IT
//********************
void main(void)
{
    Start_DSP();

    for(;;)
    {
        asm ("    NOP");
        UPDATE_ALL_EPWM_SYNC();
    }
}

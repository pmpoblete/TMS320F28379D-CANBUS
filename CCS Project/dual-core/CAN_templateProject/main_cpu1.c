//###########################################################################
//
// FILE:   main.c
//
// TITLE:  Open Loop PS-PWM for a 7-level three-phase CHB converter
// feed-forward for variable angle testing
//
// dead-time is designed by hardware
// ADC_A interrupt triggered by ePWM1 Double Update (fs kHz)
//
//! Template Developed by:
//! Dr Ricardo P. Aguilera
//! University of Technology Sydney, Australia
//! raguilera@ieee.org
//!
//! Code Experiment Developed by
//! Pablo Poblete
//!
//! Fiber Optics lines verified 13/10/2022
//! Combination d1_sm1_a = 1, d2_sm1_a = 0 gives a +Vdc at the SM
//! The Delfino launchpad has been modified. DAC3, DAC4 are now ePWM7 (RC removed)
// PR debe ser sintonizado para modo operacion 6kHz
//
// default linker F2837xD_Headers_nonBIOS_cpu1.cmd
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

// Add folder for CAN bus
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/inc/hw_types.h"
#include "driverlib/inc/hw_memmap.h"
#include "driverlib/inc/hw_can.h"
#include "driverlib/can.c"
#include "device.h"


// Global Variables
//********
#define PI              3.141592653589793
#define TWO_PI          6.283185307179586
#define TWO_PI_THIRD    2.094395102393200
#define PI_INV          0.318309886183791
#define TRUE            1
#define FALSE           0

#define f0              50
#define w0              TWO_PI*f0
#define DEG2RAD         0.0174532925199432
#define RAD2DEG         57.295791433133264
#define FC_KHZ          1
#define INV_PI_DEG      0.005555555556

#define MSG_DATA_LENGTH    8



// Included Files for particular app
//********
#include "control_structures.h"
#include "controllers.h"


// Fault Thresholds
//********
#define IMAX          10              // amps


// CAN message Variables
//********
uint16_t txMsgData[8], rxMsgData[8];
unsigned int msgCount = 0;

// Controller Variables
//********
struct duty_cycles duty_cycles;
float d = 0;
float ma = 0.762000024;
float ma_CL = 0;
float wt = 0;
unsigned int toggle_direction = 0; 
unsigned int fault = 0;
float phi_deg = 0;
float phi_rad = 0;
unsigned int CL = 1;


// debug computation
unsigned int aux = 0;
unsigned int aux1 = 0;
unsigned int aux2 = 0;
unsigned int aux3 = 0;


// Converter Parameters
float Vdc = 3*50;                    // maximum dc voltage per arm
float R = 18;                        // load resistance
float L = 0.01;                      // filter inductance
float w_zero = w0;


// user inputs
unsigned int variable_angle = 1;
unsigned int EN_user = 0;
unsigned int PWM_mod = DoubleUpdate;  // SingleUpdate_Zero, DoubleUpdate, SingleUpdate_Max
unsigned int VA_mod = 1;              // 1: VA standar, 2: VA genetic algorithm


// Controller parameters
float tc = ((float) 1) / ((float) 1000*FC_KHZ);


// Sensors
struct sensor sensor_current_a;
struct sensor sensor_current_b;
struct sensor sensor_current_c;


// State Equations
struct states states;


// Maximum available dc voltage per arm
struct abc_v arm_VDC;


// Nominal voltage for each sm per phase
struct abc_v vdc_nom_sm;


// Analog outputs
struct AnalogOutputs AnalogOutputs;


// control references
struct references references;


// control inputs
struct control_inputs control_inputs;
struct control_inputs control_inputs0;


// digital outputs
struct DigitalOutputs DigitalOutputs;


// controllers
struct PRcontroller PRalpha;
struct PRcontroller PRbeta;


// modulating indexes
struct signal_x_sm modulating_index_default;
struct signal_x_sm modulating_index;
struct signal_x_sm ps_angles;
struct signal_x_sm ps_angles_aux;
struct signal_x_sm ps_angles0;
struct signal_x_sm a1;
struct signal_x_sm ma_sms;


// normalized SM capacitor voltages
struct signal_x_sm vdc_SMs_norm;


// Function Prototypes
void DSP_Setup(void);
void DT_Control_Loop(void);
void write_outputs(struct duty_cycles duty_cycles, 
                struct DigitalOutputs DigitalOutputs, 
                struct AnalogOutputs AnalogOutputs);
void write_angles(struct signal_x_sm ps_angles);


// Main Loop
//********
void main(void)

{
    // DO NOT CHANGE THE CODE BELOW
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
    /* 1. Select Board
    _______________________________________________________________________*/
    BOARD_LAUNCHXL();
    //BOARD_controlCARD();

    /* 2. Set EPWMs
    _______________________________________________________________________*/
    // Create 12 Independent Symmetric Synchronized PWMs  /\/\/\/\/\/
    // from EPM1A to EPWM6A and from EPM1B to EPWM6B
    // set_ALL_ePWMs_SYMM_kHz(x); where x is freq in kHz

    // Set Pins for non default PWM outputs
    GPIO_SetupPinMux(157, GPIO_MUX_CPU1, 1);    // EPWM7A modified launchpad (RC removed)
    GPIO_SetupPinMux(158, GPIO_MUX_CPU1, 1);    // EPWM7B modified launchpad (RC removed)
    GPIO_SetupPinMux(14, GPIO_MUX_CPU1, 1);     // EPWM8A
    GPIO_SetupPinMux(15, GPIO_MUX_CPU1, 1);     // EPWM8B
    GPIO_SetupPinMux(16, GPIO_MUX_CPU1, 5);     // EPWM9A
    GPIO_SetupPinMux(18, GPIO_MUX_CPU1, 5);     // EPWM10A 18
    GPIO_SetupPinMux(19, GPIO_MUX_CPU1, 5);     // EPWM10B 19
    GPIO_SetupPinMux(22, GPIO_MUX_CPU1, 5);     // EPWM12A


    // set carrier frequency
    set_ALL_ePWMs_SYMM_kHz(1*FC_KHZ);  // All 24 PWMs with the same frequency

    // set frequency for PWM to sync control action
    // set_ePWM_Freq_MULT(1, 2);

    // Reduce to 6 Complementary Symmetric Synchronized PWMs
    // from EPM1 to EPWM6 -->  EPWxA = NOT(EPWMxB)
    // set_ALL_ePWMs_SYMM_COMP(x); where x is dead-time in nano sec

    // Phase shifted PWM
    ps_angles = init_ps_angles(0);                           // input = 0 -> 0,60,120 degrees init
    write_angles(ps_angles);


    // 3. Set ADCs -- One channel per ADC_x (only 4 conversions, one per x module)
    //_________________________________________________________________

    //Options: SingleUpdate_Zero
    //         SingleUpdate_Max
    //         DoubleUpdate
    //set_ADC_ePWM_SYNC(1, SingleUpdate_Zero);  // sync with PWM 7
    EPWM_IND(11,1*FC_KHZ);
    set_ADC_ePWM_SYNC(11, DoubleUpdate);

    //Set ADC parallel conversions (A,B,C,D)
    set_ADC_parallel_conv_ABCD(2,2,2,2);      //ADCINA2, ADCINB2, ADCINC2, ADCIND2 at the same time

    // 4. Set DACs
    //_________________________________________________________________
    set_DAC_A();
    set_DAC_B();     //DAC DACOUTB       J7 pin70 in BOARD_LAUNCHXL
    // launchpad PWM based DACs: GPIO 159-160


    // 5. Set General Purpose IOs  (16 to 28)
    //_________________________________________________________________
    GPIO_Mode(DigitalOutputs.EN1,OUTPUT);         // Enable 1
    GPIO_Mode(DigitalOutputs.EN2,OUTPUT);         // Enable 2
    GPIO_Mode(DigitalOutputs.comp_time,OUTPUT);   // computation time
    GPIO_Mode(DigitalOutputs.trigger,OUTPUT);     // scope trigger
    GPIO_Mode(31, OUTPUT);                        // LED


    UpdateEPwm1();                       // needs manual update
    UpdateEPwm2();
    UpdateEPwm3();
    UpdateEPwm4();
    UpdateEPwm5();
    UpdateEPwm6();
    UpdateEPwm7();
    UpdateEPwm8();
    UpdateEPwm9();
    UpdateEPwm10();
    UpdateEPwm12();


    // 7. CAN Port
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


/*
 * function:  write_outputs
 * --------------------
 * Description: assign duty-cycles to its corresponding 
 * PWM channel based on the experimental setup
 *
 * inputs______
 * 1) duty_cycles: structure with duty-cycle values
 * 2) DigitalOutputs: structure with digital outputs values
 * 3) AnalogOutputs: structure with analog output values
 *
 * 
 * connections from top->bottom, left->right in the board
 */
void write_outputs(struct duty_cycles duty_cycles, 
                struct DigitalOutputs DigitalOutputs, 
                struct AnalogOutputs AnalogOutputs)
{
    // ______ Phase-A ________ (verified 13/10/22)
    // SM 1:
    write_ePWMxA(1, 0.5);      // 1-leg cell 1 phase-a (label uC: 1)
    // write_ePWMxB(1,0.7);      // 2-leg cell 1 phase-a (label uC: 2)
    write_ePWMxA(7, duty_cycles.d1_sm1_a);
    write_ePWMxB(7, duty_cycles.d2_sm1_a);
    // SM 2:
    write_ePWMxB(2,duty_cycles.d1_sm2_a);      // 1-leg cell 2 phase-a (label uC: 3)
    write_ePWMxA(2,duty_cycles.d2_sm2_a);      // 2-leg cell 2 phase-a (label uC: 4)
    // SM 3:
    write_ePWMxB(3,duty_cycles.d1_sm3_a);      // 1-leg cell 3 phase-a (label uC: 5)
    write_ePWMxA(3,duty_cycles.d2_sm3_a);      // 2-leg cell 3 phase-a (label uC: 6)

    // ______ Phase-B ________
    // SM 1:
    write_ePWMxA(4,duty_cycles.d1_sm1_b);      // 1-leg cell 1 phase-b (label uC: 7)
    write_ePWMxB(4,duty_cycles.d2_sm1_b);      // 2-leg cell 1 phase-b (label uC: 8)
    // SM 2:
    write_ePWMxA(5,duty_cycles.d1_sm2_b);      // 1-leg cell 2 phase-b (label uC: 9)
    write_ePWMxB(5,duty_cycles.d2_sm2_b);      // 2-leg cell 2 phase-b (label uC: 10)
    // SM 3:
    write_ePWMxA(6,duty_cycles.d1_sm3_b);      // 1-leg cell 3 phase-b (label uC: 11)
    write_ePWMxB(6,duty_cycles.d2_sm3_b);      // 2-leg cell 3 phase-b (label uC: 12)

    // ______ ENABLES ________ 0 means ok. 1 is fault due to inverse logic in hardware
    GPIO_WritePin(DigitalOutputs.EN1, duty_cycles.EN1);        // top rack
    GPIO_WritePin(DigitalOutputs.EN2, duty_cycles.EN2);        // bottom rack

    // ______ Phase-C ________
    // SM 1:
    write_ePWMxA(12,duty_cycles.d1_sm1_c);      // 1-leg cell 1 phase-c (label uC: 15)
    write_ePWMxA(9,duty_cycles.d2_sm1_c);       // 2-leg cell 1 phase-c (label uC: 14)
    // SM 2:
    write_ePWMxB(10,duty_cycles.d1_sm2_c);     // 1-leg cell 2 phase-c (label uC: 13)
    write_ePWMxA(10,duty_cycles.d2_sm2_c);     // 2-leg cell 2 phase-c (label uC: 16)
    // SM 3:
    write_ePWMxB(8,duty_cycles.d1_sm3_c);      // 1-leg cell 3 phase-c (label uC: 17)
    write_ePWMxA(8,duty_cycles.d2_sm3_c);      // 2-leg cell 3 phase-c (label uC: 18)


    // _________DAC Outputs
    write_DACA_pu(AnalogOutputs.analog_out1);
    write_DACB_pu(AnalogOutputs.analog_out2);

}


/*
 * function:  write_angles
 * --------------------
 * Description: assign phase shifted angles to its corresponding
 * PWM channel based on a structure of angles
 *
 * inputs______
 * 1) ps_angles: structure with angle values
 *
 */
void write_angles(struct signal_x_sm ps_angles)
{
    set_ePWM_PS_DEG_VA(2,ps_angles.sm2_a);    // SM 2 phase-a
    set_ePWM_PS_DEG_VA(3,ps_angles.sm3_a);    // SM 3 phase-a

    set_ePWM_PS_DEG_VA(5,ps_angles.sm2_b);    // SM 2 phase-b
    set_ePWM_PS_DEG_VA(6,ps_angles.sm3_b);    // SM 3 phase-b

    set_ePWM_PS_DEG_VA(8,ps_angles.sm2_c);    // SM 2 phase-c
    set_ePWM_PS_DEG_VA(10,ps_angles.sm3_c);   // SM 3 phase-c

}

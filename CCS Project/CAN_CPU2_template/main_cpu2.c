//###########################################################################
//
// FILE:   main.c
//
// TITLE:  CAN minimum Code
//
// dead-time is designed by hardware
// ADC_A interrupt triggered by ePWM1 Double Update (fs kHz)
//
//! Template Developed by:
//! Dr Ricardo P. Aguilera and Pablo Poblete
//! University of Technology Sydney, Australia
//! pmpoblete@ieee.org
//!
//!
//###########################################################################


// Included Files for general purpose
#include "F28x_Project.h"
#include "math.h"

#ifdef _FLASH
//
// These are defined by the linker (see device linker command file)
//
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsRunStart;
#endif

// Add folder F2837xD_UTS_includes_v02 in Include Options
#include "F2837xD_MyVars_Settings_v02.h"
#include "F2837xD_MyDSP_Settings_v02_cpu2.h"
extern void DelayUs(Uint16);

// Add folder for CAN bus
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/inc/hw_types.h"
#include "driverlib/inc/hw_memmap.h"
#include "driverlib/inc/hw_can.h"
#include "driverlib/can.c"
#include "device.h"


#define MSG_DATA_LENGTH    8

// CAN message Variables
//********
uint16_t txMsgData[8], rxMsgData[8];
unsigned int msgCount = 0;
unsigned int aux = 0;


// Function Prototypes
void DSP_Setup(void);


// Main Loop
//********
void main(void)
{
    Start_DSP();    // register init

    for(;;)
    {
        asm ("    NOP");

        // Read CAN message object 2 and check for new data
        if (CAN_readMessage(CANB_BASE, 2, rxMsgData))
        {
            msgCount++;
            // Send the same message only once
            CAN_setupMessageObject(CANB_BASE, 1, 660, CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0, 0, MSG_DATA_LENGTH);
            CAN_sendMessage(CANB_BASE, 1, MSG_DATA_LENGTH, rxMsgData);
            CAN_clearMessage(CANB_BASE, 1);
            // Blink Led
            GPIO_WritePin(34, 0);
            DelayUs(100);
            GPIO_WritePin(34, 1);
            DelayUs(100);
        }


       // Send the message only once
        if (aux){
            CAN_setupMessageObject(CANB_BASE, 1, 660, CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0, 0, MSG_DATA_LENGTH);
            CAN_sendMessage(CANB_BASE, 1, MSG_DATA_LENGTH, txMsgData);
            CAN_clearMessage(CANB_BASE, 1);
            // Blink Led
            GPIO_WritePin(34, 0);
            DelayUs(10000000);
            GPIO_WritePin(34, 1);
            DelayUs(10000000);
        }

    }
}


// DSP Settings
//********
void DSP_Setup()
{
    // CAN Port
    //_________________________________________________________________

    // Initialize the CAN controller
    EALLOW;
    CpuSysRegs.PCLKCR10.bit.CAN_B = 1;
    //ClkCfgRegs.CLKSRCCTL2.bit.CANBBCLKSEL = 0;
    EDIS;

    int i;
    for (i=0; i<50; i++)
    {
        GPIO_WritePin(34, 0);
        DelayUs(10000000);
        GPIO_WritePin(34, 1);
        DelayUs(10000000);
    }


    // Initialize the CAN controller
    CAN_initModule(CANB_BASE);
    CAN_setBitRate(CANB_BASE, DEVICE_SYSCLK_FREQ, 1000000, 25); //25

    CAN_setupMessageObject(CANB_BASE, 1, 660, CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0, 0, MSG_DATA_LENGTH);
    CAN_setupMessageObject(CANB_BASE, 2, 0, CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0, 0, MSG_DATA_LENGTH);
    CAN_startModule(CANB_BASE);

    txMsgData[0] = 0x01;
    txMsgData[1] = 0x02;
    txMsgData[2] = 0x02;
    txMsgData[3] = 0x02;
    txMsgData[4] = 0x02;
    txMsgData[5] = 0x02;
    txMsgData[6] = 0x02;
    txMsgData[7] = 100;
    *(uint16_t *)rxMsgData = 0;


}


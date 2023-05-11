/*
 * CAN_Messages.h
 *
 *  Created on: 02-12-2020
 *      Author: Matias Bravo
 */

#ifndef CAN_MESSAGES_H_
#define CAN_MESSAGES_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct CAN
{
    uint32_t base;
    uint32_t mailBox;
    uint32_t ID;
    CAN_MsgFrameType frame;
    CAN_MsgObjType msgType;
    uint32_t maskID;
    uint32_t flags;
    uint16_t msgLen;
    uint32_t lastRxID;
} ObjectsCAN;


#define ID_CRITICAL_ORDER           0x00
#define ID_INSTRUCTION              0x08
#define ID_REQUEST                  0x10

#define ID_FAIL_MSG                 0x01
#define ID_REPLY                    0x09
#define ID_INFORMATION              0x11


//FUNCTIONS
void IntToHex_3(uint32_t input, uint16_t *a, uint16_t *b, uint16_t *c);
void IntToHex_2(uint32_t input, uint16_t *a, uint16_t *b);
uint32_t hexToInt_3(uint16_t a, uint16_t b, uint16_t c);
uint32_t hexToInt_2(uint16_t a, uint16_t b);
void ClearArray(uint16_t *arrayClear, uint16_t lengthArray);
void CANread(ObjectsCAN *can, uint16_t *msgData);
//void CANsend(uint32_t base, uint32_t objID, uint16_t msgLen, const uint16_t *msgData);
void CAN_setupStructMsgObj(ObjectsCAN can);


//**** GENERAL ****
#define OPERATION_STATE             0xA1
#define VOL_FREQ                    0xA2
#define ACT_REACT_PWR               0xA3

//**** RECEIVED ****
#define INJECT_PWR                  0xA4
#define RESET                       0x05
#define SET_ACT_REACT_PWR           0x06

#define DIRB_RX_EMERGENCY_STOP      0xA1

//**** SENDED ****
#define DIR_TX_PONG                        0xA0
#define PRELOAD                     0xA1
#define PLL_MY                      0xA2
#define FAIL_MSG                    0xA1
#define HEART_BIT                   0xA0
#define WARNING_MSG                 0xA2

// FLAGS
#define gFlagCriticalOrder          01
#define gFlagInstruction            02
#define gFlagRequest                03


//**** GENERAL ID ****
//#define FRM_ID_FAIL_MSG             0x04
//#define FRM_ID_HEART_BIT            0x05
//#define FRM_ID_REPLY                0x06
//#define FRM_ID_INFORMATION          0x07

#define BYTE_DIR_MSG                0
// message address byte in reception
#define DIR_RX_PRELOAD              0xA1
#define DIR_RX_CTTDC                0xA2
#define DIR_RX_CTTAC                0xA3
#define DIR_RX_RESET                0xA5
#define DIR_RX_SET_PWR              0xA6

//**** GENERAL VALUES ****
#define ACTIVATE                    0x00
#define DEACTIVATE                  0x01

#define PRELOAD_FINISH              0x01
#define PLL_OK                      0x01

#define STATUS_CHECK_CHANGE         0
#define STATUS_CURRENT_STATE        1

//REPLYS
#define REPLY_PONG                  0xA0
#define REPLY_OPERATION_STATE       0xA1
#define REPLY_VOLT_FREQ             0xA2
#define REPLY_PWR_ACT_REACT         0xA3

//BITS VALUE
#define DISPLACEMENT_11             2048
#define DISPLACEMENT_12             4096
#define DISPLACEMENT_15             32768
#define DISPLACEMENT_16             65536
#define DISPLACEMENT_23             8388608
#define DISPLACEMENT_24             16777216

#endif /* CAN_MESSAGES_H_ */

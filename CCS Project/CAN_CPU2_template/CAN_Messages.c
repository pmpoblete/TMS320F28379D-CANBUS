/*
 * CAN_Messages.c
 *
 *  Created on: 02-12-2020
 *      Author: Matias Bravo
 */

#include "CAN_Messages.h"


void IntToHex_3(uint32_t input, uint16_t *a, uint16_t *b, uint16_t *c)
{
    *c = input & 0xFF;
    *b = input >> 8 & 0xff;
    *a = input >> 16;
}

void IntToHex_2(uint32_t input, uint16_t *a, uint16_t *b)
{
    *b = input & 0xFF;
    *a = input >> 8;
}

uint32_t hexToInt_3(uint16_t a, uint16_t b, uint16_t c)
{
    uint32_t output = 0;;

    output |= a & 0xFF;
    output <<= 8;
    output |= b & 0xFF;
    output <<= 8;
    output |= c & 0xFF;

    return output;
}

uint32_t hexToInt_2(uint16_t a, uint16_t b)
{
    uint32_t output = 0;;

    output |= a & 0xFF;
    output <<= 8;
    output |= b & 0xFF;

    return output;
}

void ClearArray(uint16_t *arrayClear, uint16_t lengthArray)
{
    uint32_t i;
    for (i = 0; i < lengthArray; i++)
    {
        arrayClear[i] = 0x00;
    }
}

void Clear_Array(unsigned int Array[], unsigned int SizeOfArray)
{
    unsigned int i;
    for(i = 0; i < SizeOfArray; i++)
    {
        Array[i] = 0;
    }
}

void CAN_setupStructMsgObj(ObjectsCAN can)
{
    CAN_setupMessageObject(can.base, can.mailBox, can.ID, can.frame,
                           can.msgType, can.maskID, can.flags, can.msgLen);
}

void CANread(ObjectsCAN *can, uint16_t *msgData)
{
    CAN_readMessageWithID(can->base, can->mailBox, &can->frame, &can->lastRxID,
                          msgData);
}

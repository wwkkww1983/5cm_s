//===========================================================================
//文件名称：encoder.h
//功能概要：光电编码器驱动头文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-01-27  V1.0
//芯片类型：KEAZ128
//作者：Shine Wong
//===========================================================================
#include "incap.h"
#include "gpio.h"

#ifndef ENCODER_H_
#define ENCODER_H_

#define ENCODER_1 0
#define ENCODER_2 1

//define the interrupt server function of ENCODER_1 ENCODER_2
#define encoder1IRQ FTM0_IRQHandler
#define encoder2IRQ FTM1_IRQHandler

//==========================================================================
//Function: To initialize a encoder with two PWM ports
//Return: Null
//Arguements: encoderNum: select which encoder to initialize:ENCODER_1, ENCODER_2
//Others: ENCODER_1 uses FTM_0 and ENCODER_2 uses FTM_1 by default
//        PTA0 is used as FTM_0 and PTA1 is used as GPIO function
//        PTC4 is used as FTM_1 and PTC5 is used as GPIO function
//        Interrupt is enabled automatically
//==========================================================================
void initEncoder(uint_8 encoderNum);

//==========================================================================
//Function: To clear channel flag(CHF) of the FTMx_CnSC register
//Return: Null
//Arguements: encoderNum: select which encoder to clear:ENCODER_1, ENCODER_2
//Others: ENCODER_1 uses FTM_0 and ENCODER_2 uses FTM_1 by default
//==========================================================================
void EncoderClrFlag(uint_8 encoderNum);

//==========================================================================
//Function: To read the value of the COUNT register 
//Return: return the value of the counter, if the signal reverses, 
//        the return value will be a negative value
//Arguements: encoderNum: select which encoder to read:ENCODER_1, ENCODER_2
//Others: ENCODER_1 uses FTM_0 and ENCODER_2 uses FTM_1 by default
//        This function reads the COUNT register and returns the value
//==========================================================================
int_16 EncoderRead(uint_8 encoderNum);

//==========================================================================
//Function: to determine whether a encoder's channel interrupt flag(CHF) is set
//Return: returns 0 when the interrupt flag is not set and 1 when set 
//Arguements: encoderNum: select which encoder to read:ENCODER_1, ENCODER_2
//Others: the function is used as the first line of the interrupt server to avoid 
//        unnecessary problems
//==========================================================================
uint_8 isEncoderFlagSet(uint_8 encoderNum);

#endif

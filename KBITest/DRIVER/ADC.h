//===========================================================================
//文件名称：ADC.h
//功能概要：ADC模块配置头文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-01-27  V1.0
//芯片类型：KEAZ128
//作者：Shine Wong
//===========================================================================
#include "common.h"

#ifndef ADC_H_
#define ADC_H_

#define FIFODEPTH 8

#define ADC_1 11
#define ADC_2 8
#define ADC_3 14 
#define ADC_4 12
#define ADC_5 10
#define ADC_6 9
#define ADC_7 15

//===========================================================================
//Function: To initialize the ADC module
//Return: Null
//Arguements: channel
//Others: use FIFO by default whose depth is 8
//===========================================================================
void ADCInit(void);

//===========================================================================
//Function: To Read the value converted from the ADC channel
//Return: return the average of the middle 6 values stored in the FIFO queue
//Arguements: channel: the channel where the values are read and converted
//Others: the values are stored in FIFO queue with a depth of 8 by default
//===========================================================================
uint_16 ADCRead(uint_8 channel);

//===========================================================================
//Function: To Read the value converted from the ADC channel for N times
//Return: return the average of the N values obtained from ADCRead()
//Arguements: channel: the channel where the values are read and converted
//Others: this function in fact calls ADCRead() for N times and returns the average
//===========================================================================
uint_16 ADCReadn(uint_8 channel,uint_8 N);

#endif

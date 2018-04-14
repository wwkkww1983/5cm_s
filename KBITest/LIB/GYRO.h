//===========================================================================
//文件名称：GYRO.h
//功能概要：陀螺仪配置头文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-01-27  V1.0
//芯片类型：KEAZ128
//作者：Shine Wong
//===========================================================================
#include "ADC.h"

#ifndef GYRO_H_
#define GYRO_H_

/* 
 * 0.67mV/deg./sec.
 * 12bits ADC with a maximum of 4096
 * ref voltage:3.3V 
 * magnification: 6
 * (3300/4096)/(0.67*6) = 0.20041394589552233
 */
#define GYRORATIO  0.2

#define VO1 2
#define VO2 3
#define VO3 13
#define FIFODEPTH 8

//===========================================================================
//Function: To initialize the Gyroscope module
//Return: Null
//Arguements: Null
//Others: use ADC2(PTA6), ADC3(PTA7), ADC13(F5) as GYRO port
//===========================================================================
void GYROInit(void);

//===========================================================================
//Function: To Read the value converted from the GYRO channel
//Return: return the average of the middle 6 values stored in the FIFO queue
//Arguements: channel: stands for VO1 VO2 VO3 port of the GYRO
//Others: the values are stored in FIFO queue with a depth of 8 by default
//===========================================================================
uint_16 GYRORead(uint_8 channel);

//===========================================================================
//Function: To Read the value converted from the GYRO channel for N times
//Return: return the average of the N values obtained from GYRORead()
//Arguements: channel: stands for VO1 VO2 VO3 port of the GYRO
//Others: this function in fact calls GYRORead() for N times and returns the average
//===========================================================================
uint_16 GYROReadn(uint_8 channel,uint_8 N);

//===========================================================================
//Function: To solve the datas read from the gyroscope to true angular velocity
//Return: return the angular velocity solved
//Arguements: gyroValue: the primitive value read from the gyroscope
//Others: null
//===========================================================================
float GYROSolve(uint_16 gyroValue);

//===========================================================================
//Function: To Read the initial gyroscope value as mid-value
//Return: return mid-value of the gyroscope
//Arguements: channel: stands for VO1 VO2 VO3 port of the GYRO
//Others: call GYROReadn() at the beginning of the programme
//===========================================================================
uint_16 getGyroMid(uint_8 channel);

#endif

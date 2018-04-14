//===========================================================================
//文件名称：motor.h
//功能概要：电机驱动头文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-01-23  V1.0
//芯片类型：KEAZ128
//作者：Shine Wong
//===========================================================================
#include "pwm.h"

#ifndef MOTOR_H_
#define MOTOR_H_

//define the motors
#define MOTOR_1 1
#define MOTOR_2 2

//==========================================================================
//Function: To initialize a motor with two PWM ports
//Return: Null
//Arguements: motorNum: select which motor to initialize:MOTOR_1, MOTOR_2
//			  frequency: set the frequency of the PWM pulse, which ranges from 
//						 0.012 to 1500(KHz)
//Others: the initial duty is set to zero automatically
//==========================================================================
void initMotor(int motorNum,float frequency);

//==========================================================================
//Function: To set a motor's duty of forward direction
//Return: Null
//Arguements: motorNum: select which motor to initialize:MOTOR_1, MOTOR_2
//			  duty: set the duty of the PWM pulse
//==========================================================================
void setForwDuty(int motorNum,float duty);

//==========================================================================
//Function: To set a motor's duty of reverse direction
//Return: Null
//Arguements: motorNum: select which motor to initialize:MOTOR_1, MOTOR_2
//			  duty: set the duty of the PWM pulse
//==========================================================================
void setReveDuty(int motorNum,float duty);

#endif

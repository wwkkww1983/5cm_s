//===========================================================================
//文件名称：PID.h
//功能概要：PID控制头文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-03-19  V1.0
//芯片类型：KEAZ128
//作者：Shine Wong
//===========================================================================
#ifndef PID_H_
#define PID_H_

#include "common.h"

typedef struct PID {
	int_16  target;			// 设定目标 Desired value
	int_16  proportion; 	// 比例常数 Proportional Const
	int_16  integral;		// 积分常数 Integral Const
	int_16  derivative;		// 微分常数 Derivative Const
	int_16  lastError; 		// Error[−1]
	int_16  prevError; 		// Error[−2]
	int_16  sumError; 		// Sums of Errors
	int_16  lastOutput;		// Control quantity last time
}PID,*pPID;

//===========================================================================
//Function: Initialize PID structure parameters.
//Return: null
//Arguements: pidController: a certain PID Controller(a pointer) with parameters set
//			  Kp,Ki,Kd:   	 p,i,d parameters for PID structure
//Others: null
//===========================================================================
void PIDInit(pPID pidController, int_16 Kp, int_16 Ki, int_16 Kd);
//===========================================================================
//Function: To compute the control quantity according to a certain PID Controller
//			and an error value
//Return: returns control quantity
//Arguements: pidController: a certain PID Controller(a pointer) with parameters set
//			  thisError:   	 the most lately computed error
//Others: null
//===========================================================================
int PIDController(pPID pidController, int_16 thisError);

#endif

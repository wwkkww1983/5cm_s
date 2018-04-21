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
	float  target;			// 设定目标 Desired value
	float  proportion; 		// 比例常数 Proportional Const
	float  integral;		// 积分常数 Integral Const
	float  derivative;		// 微分常数 Derivative Const
	float  lastError; 		// Error[−1]
	float  prevError; 		// Error[−2]
	float  sumError; 		// Sums of Errors
	float  lastOutput;		// Control quantity last time
}PID,*pPID;

//===========================================================================
//Function: Initialize PID structure parameters.
//Return: null
//Arguements: pidController: a certain PID Controller(a pointer) with parameters set
//			  Kp,Ki,Kd:   	 p,i,d parameters for PID structure
//Others: null
//===========================================================================
void PIDInit(pPID pidController, float Kp, float Ki, float Kd);
//===========================================================================
//Function: To compute the control quantity according to a certain PID Controller
//			and an error value
//Return: returns control quantity
//Arguements: pidController: a certain PID Controller(a pointer) with parameters set
//			  thisError:   	 the most lately computed error
//Others: null
//===========================================================================
//int PIDController(pPID pidController, float thisError);
//===========================================================================
//Function: To compute the control quantity according to a certain PID Controller
//			and an error value
//Return: returns control quantity
//Arguements: pidController: a certain PID Controller(a pointer) with parameters set
//			  gloal:   	 target value
//			  thisVal:   current value
//Others: null
//===========================================================================
float PIDcalc(pPID pidController, float gloal, float thisVal);

#endif

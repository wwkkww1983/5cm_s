//===========================================================================
//文件名称：PID.c
//功能概要：PID控制源文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-03-19  V1.0
//芯片类型：KEAZ128
//作者：Shine Wong
//===========================================================================
#include "PID.h"

//===========================================================================
//Function: Initialize PID structure parameters.
//Return: null
//Arguements: pidController: a certain PID Controller(a pointer) with parameters set
//			  Kp,Ki,Kd:   	 p,i,d parameters for PID structure
//Others: null
//===========================================================================
void PIDInit(pPID pidController, float Kp, float Ki, float Kd)
{
	pidController->proportion = Kp;
	pidController->integral = Ki;
	pidController->derivative = Kd;
	pidController->target = 0;
	pidController->lastError = 0;
	pidController->prevError = 0;
	pidController->sumError = 0;
	pidController->lastOutput = 0;
}
//===========================================================================
//Function: To compute the control quantity according to a certain PID Controller
//			and an error value
//Return: returns control quantity
//Arguements: pidController: a certain PID Controller(a pointer) with parameters set
//			  thisError:   	 the most lately computed error
//Others: null
//===========================================================================
//int PIDController(pPID pidController, float thisError){
//	float pError, dError, iError, output;
//	pError = thisError - pidController->lastError;
//	iError = thisError;
//	dError = thisError - 2*(pidController->lastError) + pidController->prevError;
//	output = pidController->proportion*pError + pidController->integral*iError + pidController->derivative*dError;
//	pidController->prevError   = pidController->lastError;
//	pidController->lastError  = thisError;
//	pidController->lastOutput = output + pidController->lastOutput;
////	return pidController->lastOutput;
//	return output;
//}


//	pidController->proportion = Kp;
//	pidController->integral = Ki;
//	pidController->derivative = Kd;
//	pidController->target = 0;
//	pidController->lastError = 0;
//	pidController->prevError = 0;
//	pidController->sumError = 0;
//	pidController->lastOutput = 0;
float PIDcalc(pPID pidController, float gloal, float thisVal){
	float error,output;
	error = gloal - thisVal;
	pidController->sumError += error;
	output = pidController->proportion*error + pidController->integral*pidController->sumError + pidController->derivative*(pidController->lastError-error);
	pidController->lastError  = error;
	pidController->lastOutput = thisVal + output;
	return pidController->lastOutput;
}


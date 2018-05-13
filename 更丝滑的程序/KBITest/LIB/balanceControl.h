//===========================================================================
//文件名称：balanceControl.h
//功能概要：主方向控制环程序头文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-03-18  V1.0
//芯片类型：KEAZ128
//作者：Shine Wong
//===========================================================================
#ifndef BALANCECONTROL_H_
#define BALANCECONTROL_H_

//#include "PID.h"
#include "GYRO.h"
#include "accelerometer.h"
#include "math.h"

#define BALANCECOUNT 4			//excute balance control every 10ms(read datas for 5 times)
#define CONTROLTIME 0.005		//5ms
#define INITIAL_COVARIANCE 10	//initial covariance of the optimum angle
#define Q					3			//covariance of the datas read from the gyroscope
#define R 				300		//covariance of the datas read from the accelerometer

#define PI 3.14159265358979

//===========================================================================
//Function: reads datas from the gyro&acce and computes the kalman angle and 
//			controls the motor
//Return: null(error handler)
//Arguements: null
//Others: this function is main control programme of the autocar's balance
//===========================================================================
//void balanceControl(pPID balancePID);

//===========================================================================
//Function: To deal with the datas read by the gyro&acce using kalman filter
//Return: returns the angle obtained from the kalman filter
//Arguements: angVelocity: the angular velocity solved from the gyroscope
//			  acceAngle:   the angle solved from the accelerometer
//Others: the covariance is defined at the beginning of this file
//===========================================================================
float KALMANFilter(float angVelocity, float acceAngle);

#endif

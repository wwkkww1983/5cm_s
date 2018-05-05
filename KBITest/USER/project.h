//===========================================================================
//文件名称：PROJECT.h
//功能概要：工程全局头文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-04-18 v1.0
//芯片类型：KEAZ128
//作者：	    YTom
//===========================================================================
#ifndef PROJECT_H_
#define PROJECT_H_

#include "KBI.h"
#include "balanceControl.h"
#include "OLED.h"
#include "GYRO.h"
#include "pit.h"
#include "delay.h"
#include "display.h"
#include "string.h"
#include "accelerometer.h"
#include "incap.h"
#include "motor.h"
#include "encoder.h"
#include "PID.h"
#include "includes.h"
#include "math.h"

/*flags of some peripherals to detect whether they are to be operated*/
#define ADC_READ_FLAG			(peripheralRun&(0x01))		// No use
#define GYRO_ACCE_FLAG			(peripheralRun&(0x02))		// For GYRO and ACCE data read
#define POSITION_FLAG			(peripheralRun&(0x04))		// No use
#define ENCODER_FLAG			(peripheralRun&(0x08))		// No use
#define SPEED_CONTROL			(peripheralRun&(0x10))		// For speed PID
#define DIRECTION_CONTROL		(peripheralRun&(0x20))		// No use
#define BALANCE_CONTROL 		(peripheralRun&(0x40))
#define DISP_REFRESH			(peripheralRun&(0x80))		// For display periodic updates

#define SET_ADCREAD_FLAG()		(peripheralRun|=(0x01))
#define SET_GYROACCE_FLAG()		(peripheralRun|=(0x02))
#define SET_POSITION_FLAG()		(peripheralRun|=(0x04))
#define SET_ENCODER_FLAG()		(peripheralRun|=(0x08))
#define SET_SPEED_CONTROL()		(peripheralRun|=(0x10))
#define SET_DIRECTION_CONTROL()	(peripheralRun|=(0x20))
#define SET_BALANCE_CONTROL()	(peripheralRun|=(0x40))
#define SET_DISP_REFRESH()		(peripheralRun|=(0x80))

#define CLR_ADCREAD_FLAG()		(peripheralRun&=~(0x01))
#define CLR_GYROACCE_FLAG()		(peripheralRun&=~(0x02))
#define CLR_POSITION_FLAG()		(peripheralRun&=~(0x04))
#define CLR_ENCODER_FLAG()		(peripheralRun&=~(0x08))
#define CLR_SPEED_CONTROL()		(peripheralRun&=~(0x10))
#define CLR_DIRECTION_CONTROL()	(peripheralRun&=~(0x20))
#define CLR_BALANCE_CONTROL()	(peripheralRun&=~(0x40))
#define CLR_DISP_REFRESH()		(peripheralRun&=~(0x80))

#define GLOBAL_TIME_UNIT		500
#define ADCREAD_TIME			2u 			//read ADC every 				1ms		1000Hz
#define GYRO_ACCE_TIME			2u 			//read gyro&acce every 			1ms		1000Hz
#define POSITION_TIME			2u 			//compute position every 		1ms		1000Hz
#define ENCODER_TIME			8u			//read encoder every 			4ms		250Hz
//#define SPEED_CONTRO_LTIME		8u			//run speed control every 		4ms		250Hz
#define SPEED_CONTRO_LTIME		10u			//run speed control every 		20ms		200Hz
#define DIR_CONTROL_TIME		10u			//run direction control every 	5ms		200Hz
#define BALANCE_CONTROL_TIME	40u			//run balance control every 	5ms		200Hz
#define OLED_CHANGE_TIME		1000u		//update oled display every 	500ms	2Hz
//#define ELAPSE_TIME				1000u		//elapse time 20ms


#define KBIMASK 			(kbi_Press1|kbi_Press2|kbi_Press3|kbi_Press4|kbi_Press5|kbi_Press6)
#define ANTISHAKETIME 		30

/*RUNNING MODE DEFINITIONS: 'OLED MODE','BALANCE MODE','DRIVING MODE'*/
#define IS_OLED_MODE 			(runningMode&(0x01))
#define IS_BALANCE_MODE			(runningMode&(0x02))
#define IS_DRIVING_MODE			(runningMode&(0x04))
#define IS_CLEAR_OLED			(runningMode&(0x08))

#define SET_OLED_MODE()			(runningMode|=(0x01))
#define SET_BALANCE_MODE()		(runningMode|=(0x02))
#define SET_DRIVING_MODE()		(runningMode|=(0x04))
#define SET_CLEAR_OLED()		(runningMode|=(0x08))

#define CLR_OLED_MODE()			(runningMode&=~(0x01))
#define CLR_BALANCE_MODE()		(runningMode&=~(0x02))
#define CLR_DRIVING_MODE()		(runningMode&=~(0x04))
#define CLR_CLEAR_OLED()		(runningMode&=~(0x08))

extern uint_8 	peripheralRun;
extern uint_8 	runningMode;

extern uint_8 	rawAcce[8];
extern int_16 	acceValue[3];
extern int_16 	gyroValue[5], xAxis[5], zAxis[5], angVelocity, xAxisMean, zAxisMean, gyroMean;
extern int_16 	acceAngle, gyroAngle;
extern float	KalmanAngle;

// For encoder (velocity feedback)
extern int_16 	countLoop[2];		// 
extern float 	speedRPM[2];		// For PID
extern int_16 	frequency[2];		// Display conertion value for speedRPM
extern float 	sendSpeed[2];		// Speed sent to motor
extern int_16 	sSpeed[2];			// Display conertion value for sendSpeed
extern float 	setGoalRPM[2];		// Speed Goal

extern PID 		PID_Speed[2];
extern int_16 	PID_p;				// 
extern int_16 	PID_i;				// 
extern int_16 	PID_d;				// 
extern int_16 	maxLIM;				// 

extern int_16	speedIndex;


extern int_16 globalCount;

void globalResetMid(void);

#endif /* PROJECT_H_ */


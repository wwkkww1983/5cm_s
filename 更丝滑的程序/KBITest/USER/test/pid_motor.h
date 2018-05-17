/*
 *--------------------------------------------------------------------------------
 *	FileName		pid_motor.h	
 *	Brief			Test for PID module
 *	Microchip		KEA128
 *	Author			YTom
 *	E-mail			ybb331082@126.com
 *	ModifyTime		
 *	Copyright 		2017 TU-Smart. All Rights Reserved.
 *	Attention		PID module
 *					PWM module
 *--------------------------------------------------------------------------------
 */

#include "pwm.h"
#include "PID.h"


#define motor_FTM			FTM_0
#define motor_CHNNALE		0
#define motor_FREQUENCY		1.0


#define speed_P		1
#define speed_I		0
#define speed_D		0


extern pPID PIDSpeed;
extern float motor_DutyGoal;

void motor_Init(void);


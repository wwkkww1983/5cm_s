//===========================================================================
//文件名称：motor.c
//功能概要：电机驱动头文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-01-23  V1.0
//芯片类型：KEAZ128
//作者：Shine Wong
//===========================================================================
#include "motor.h"
//==========================================================================
//Function: To initialize a motor with two PWM ports
//Return: Null
//Arguements: motorNum: select which motor to initialize:MOTOR_1, MOTOR_2
//			  frequency: set the frequency of the PWM pulse, which ranges from 
//						 0.012 to 1500KHz
//Others: the initial duty is set to zero automatically
//==========================================================================
void initMotor(int motorNum,float frequency){
	switch(motorNum){
		case MOTOR_1:
			FTM_PWM_init(FTM_2,CHANNEL0,frequency,0);
			FTM_PWM_init(FTM_2,CHANNEL1,frequency,0);
			break;

		case MOTOR_2:
			FTM_PWM_init(FTM_2,CHANNEL2,frequency,0);
			FTM_PWM_init(FTM_2,CHANNEL3,frequency,0);
			break;

		//still remain to fill the content
		default:
			break;
	}
}

//==========================================================================
//Function: To set a motor's duty of forward direction
//Return: Null
//Arguements: motorNum: select which motor to initialize:MOTOR_1, MOTOR_2
//			  duty: set the duty of the PWM pulse
//==========================================================================
void setForwDuty(int motorNum,float duty){
	switch(motorNum){
		case MOTOR_1:
			FTM_PWM_set_duty(FTM_2,CHANNEL0,speedLeagalize(duty));
			FTM_PWM_set_duty(FTM_2,CHANNEL1,0);
			break;

		case MOTOR_2:
			FTM_PWM_set_duty(FTM_2,CHANNEL2,speedLeagalize(duty));
			FTM_PWM_set_duty(FTM_2,CHANNEL3,0);
			break;

		//still remain to fill the content
		default:
			break;

	}
}

//==========================================================================
//Function: To set a motor's duty of reverse direction
//Return: Null
//Arguements: motorNum: select which motor to initialize:MOTOR_1, MOTOR_2
//			  duty: set the duty of the PWM pulse
//==========================================================================
void setReveDuty(int motorNum,float duty){
	switch(motorNum){
		case MOTOR_1:
			FTM_PWM_set_duty(FTM_2,CHANNEL0,0);
			FTM_PWM_set_duty(FTM_2,CHANNEL1,speedLeagalize(duty));
			break;

		case MOTOR_2:
			FTM_PWM_set_duty(FTM_2,CHANNEL2,0);
			FTM_PWM_set_duty(FTM_2,CHANNEL3,speedLeagalize(duty));
			break;

		//still remain to fill the content
		default:
			break;
		}
}


float calcDuty(float speedrpm)
{
	return 0.03*speedrpm+20.0;
}

float speedLeagalize(float duty)
{
	return (duty<0)?0:((duty>MOTOR_SPEEDLIMIT)?MOTOR_SPEEDLIMIT:duty);
}

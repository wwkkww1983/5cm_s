
#include "pid_motor.h"

pPID PIDSpeed;
float motor_DutyGoal;


void motor_Init(void)
{
	PIDInit(PIDSpeed,speed_P,speed_I,speed_D);
	FTM_PWM_init(motor_FTM,motor_CHNNALE,motor_FREQUENCY,0);				// PWM: 1.0KHz, 0%;
	motor_DutyGoal = 0;
}

void motor_Update()
{
	PIDSpeed->target = motor_DutyGoal;
	
	FTM_PWM_set_duty(motor_FTM,motor_CHNNALE);
	PIDController(PIDSpeed,
}

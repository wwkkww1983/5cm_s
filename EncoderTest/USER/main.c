#include "incap.h"
#include "motor.h"
#include "encoder.h"

uint_16 frequency;

int main(){
	  //initialization
    initEncoder(ENCODER_2);
	  initEncoder(ENCODER_1);
	  //SIM_SOPT0 &= ~SIM_SOPT0_SWDE_MASK;
	  //INCaptureInit(FTM_1,CHANNEL0);
	  //FTMEnInterrupt(FTM_1);
	  initMotor(MOTOR_1,10);
	  initMotor(MOTOR_2,10);
	  //gpio_init(PORTC|(7),GPIO_OUTPUT,0);
	  gpio_init(PORTA|(3),GPIO_OUTPUT,0);
	
	  setForwDuty(MOTOR_1,30);
	  setReveDuty(MOTOR_2,30);
	  //gpio_set(PORTC|(7),1);
	  gpio_set(PORTA|(3),1);
	  while(1);
}

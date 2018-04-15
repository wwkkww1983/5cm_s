#include "incap.h"
#include "motor.h"
#include "encoder.h"
#include "pit.h"
#include "OLED.h"

uint_16 frequency[2] = {0};

uint8_t GREG = 0x00;
uint8_t cnt = 0;

#define GREG_OLEDF			0x01

int main(){
	OLED_Init();
	OLED_Clear();
	OLED_ShowString(0,0,"Enc0:");
	OLED_ShowString(0,2,"Enc1:");
	
	pitInit_us(pit_CH0,500000);
	
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

	setForwDuty(MOTOR_1,25);
	setReveDuty(MOTOR_2,25);
	//gpio_set(PORTC|(7),1);
	gpio_set(PORTA|(3),1);

	while(1) {
		if(GREG&GREG_OLEDF) {
			cnt++;
			GREG &= ~GREG_OLEDF;
			OLED_ShowNum(40,0,frequency[0],5,20);
			OLED_ShowNum(40,2,frequency[1],5,20);
			OLED_ShowNum(0,4,cnt,3,SIZE);
		}
	}
}


void PIT_CH0_IRQHandler(void){

	GREG |= GREG_OLEDF;
	
	pit_IRQClearFlag(pit_CH0);
}





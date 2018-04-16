#include "incap.h"
#include "motor.h"
#include "encoder.h"
#include "pit.h"
#include "OLED.h"
#include "display.h"
#include "string.h"
#include "PID.h"

// Encoder: 375KHz ()pulses/circle

int_16 frequency[2] = {0};
float speedRPM[2] = {0.};

uint8_t GREG = 0x00;
int16_t timeCOUNT = 0;
displayItem items[DATANUM];



#define GREG_OLEDF			0x01

int main(){
	// Display data
	OLED_Init();
	OLED_Clear();
	strcpy(items[0].argName,"va0:");
	items[0].argValue = &frequency[0];
	items[0].delta = 0;

	strcpy(items[1].argName,"va1:");
	items[1].argValue = &frequency[1];
	items[1].delta = 0;
	
	strcpy(items[2].argName,"Cnt:");
	items[2].argValue = &timeCOUNT;
	items[2].delta = 0;
	
	pitInit_ms(pit_CH0,1000);
	GREG |= GREG_OLEDF;
	
	//initialization
	initEncoder(ENCODER_2);
	initEncoder(ENCODER_1);
	initMotor(MOTOR_1,10);
	initMotor(MOTOR_2,10);
	
	//
	gpio_init(PORTA|(3),GPIO_OUTPUT,0);
	gpio_set(PORTA|(3),1);
	setForwDuty(MOTOR_1,20);
	setReveDuty(MOTOR_2,20);
	
	while(1) {
		if(GREG&GREG_OLEDF) {
			timeCOUNT++;
			GREG &= ~GREG_OLEDF;
			OLEDDisplay(items);
		}
	}
}

void PIT_CH0_IRQHandler(void){

	GREG |= GREG_OLEDF;
	
	pit_IRQClearFlag(pit_CH0);
}





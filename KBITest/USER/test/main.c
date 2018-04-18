#include "incap.h"
#include "motor.h"
#include "encoder.h"
#include "pit.h"
#include "OLED.h"
#include "display.h"
#include "string.h"
#include "PID.h"

// Encoder: 375KHz ()pulses/circle

int_16 frequency[2] = {0,0};
int_16 countLoop[2] = {0,0};
int_16 sSpeed[2] = {0,0};
float speedRPM[2] = {0.f,0.f};
float sendSpeed[2] = {0.f,0.f};

displayItem items[DATANUM];

uint8_t GREG = 0x00;
#define GREG_OLEDF			0x01
#define GREG_PID			0x02


PID PID_Speed[2];
float setGoalRPM = 0;
#define PID_p	1.5f
#define PID_i	0.f
#define PID_d	0.f


int main(){
	// Display data
	OLED_Init();
	OLED_Clear();
	strcpy(items[0].argName,"va0:");		// Data1
	items[0].argValue = &frequency[0];
	items[0].delta = 0;
	strcpy(items[1].argName,"va1:");		// Data2
	items[1].argValue = &frequency[1];
	items[1].delta = 0;
	strcpy(items[2].argName,"Cnt1:");		// Data3
	items[2].argValue = &sSpeed[0];
	items[2].delta = 0;
	strcpy(items[3].argName,"Cnt2:");		// Data4
	items[3].argValue = &sSpeed[1];
	items[3].delta = 0;
	
	pitInit_us(pit_CH0,10000);
	GREG |= GREG_OLEDF;
	GREG &= ~GREG_PID;
	
	// PID initialization
	PIDInit(&PID_Speed[0],PID_p,PID_i,PID_d);
	PIDInit(&PID_Speed[1],PID_p,PID_i,PID_d);
	// Encoders initialization
	initEncoder(ENCODER_2);
	initEncoder(ENCODER_1);
	// Motors initialization
	initMotor(MOTOR_1,10);	// 10kHz
	initMotor(MOTOR_2,10);

	setGoalRPM = 400.0;
	
	while(1) {
		if(GREG&GREG_OLEDF) {
			GREG &= ~GREG_OLEDF;
			OLEDDisplay(items);
		}
		if(GREG&GREG_PID) {
			GREG &= ~GREG_PID;
			sendSpeed[0] = calcDuty(PIDcalc(&PID_Speed[0],setGoalRPM,speedRPM[0]));
			sendSpeed[1] = calcDuty(PIDcalc(&PID_Speed[1],setGoalRPM,speedRPM[1]));
			setForwDuty(MOTOR_1,sendSpeed[0]);
			setForwDuty(MOTOR_2,sendSpeed[1]);
			sSpeed[0] = (int16_t)sendSpeed[0];
			sSpeed[1] = (int16_t)sendSpeed[1];
		}
	}
}

void PIT_CH0_IRQHandler(void){
	static uint_32 count = 0;
	count++;
	
	if(count%2==0) {
		GREG |= GREG_PID;
	} 
	if(count%100==0) {
		GREG |= GREG_OLEDF;
	}
//	if(count%100==0) {
//		timeCOUNT++;
//	}
	
	pit_IRQClearFlag(pit_CH0);
}





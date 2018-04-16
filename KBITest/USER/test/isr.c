#include "encoder.h"
#include "common.h"
#include "incap.h"
#include "gpio.h"

extern uint_16 frequency[2];
extern float speedRPM[2];
int avg = 0;

void FTM1_IRQHandler(){
	static int_16 results[10]={0};
	static uint_8 index = 0;
	if(isEncoderFlagSet(ENCODER_2)){
		results[index] = EncoderRead(ENCODER_2);
		//results[index] = FTM0_C0V;
		//direction = gpio_get(PORTA|(1));
		index++;
		if(index == 10){
			FTM1_CNT = 0;		//Clear the counter
			index = 0;
			for(uint_8 i=0;i<5;i++){
				avg+=results[i+5]-results[i];
			}
			avg=avg/25;
			speedRPM[0] = INCAP_CLOCK/60/avg/encoder1CirclePulse; // Speed in rpm
			frequency[0]=(int16_t)speedRPM[0];
		}
		EncoderClrFlag(ENCODER_2);
	}
}

void FTM0_IRQHandler(){
	static int_16 results[10]={0};
	static uint_8 index = 0;
	if(isEncoderFlagSet(ENCODER_1)){
		results[index] = EncoderRead(ENCODER_1);
		//results[index] = FTM0_C0V;
//		direction = gpio_get(PORTA|(1));
		index++;
		if(index == 10){
			FTM0_CNT = 0;		//Clear the counter
			index = 0;
			
			for(uint_8 i=0;i<5;i++){
				avg+=results[i+5]-results[i];
			}
			avg=avg/25;
			speedRPM[1] = INCAP_CLOCK/60/avg/encoder2CirclePulse; // Speed in rpm
			frequency[1]=(int16_t)speedRPM[1];
		}
		EncoderClrFlag(ENCODER_1);
	}
}

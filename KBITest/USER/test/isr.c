#include "encoder.h"
#include "common.h"
#include "incap.h"
#include "gpio.h"

extern int_16 frequency[2];
extern int_16 countLoop[2];
extern float speedRPM[2];
int avg = 0;


//传动比~3
//计算：INCAP_CLOCK*60/avg/encoder1CirclePulse; // Speed in rpm
//      375000*60/512/avg/3
#define SPEED_INDEX		14648.4f
#define LOOP_PULSE		1536

void FTM1_IRQHandler(){
	static uint_16 results[10]={0};
	static uint_8 index = 0;
	static uint_16 count = 0;
	if(isEncoderFlagSet(ENCODER_2)){
		count++;
		if(count==LOOP_PULSE){
			count=0;countLoop[0]++;
		}
		
		results[index] = EncoderRead(ENCODER_2);
		index++;
		if(index == 10){
			index = 0;
			FTM1_CNT = 0;		//Clear the counter
			for(uint_8 i=0;i<5;i++){
				avg+=results[i+5]-results[i];
			}
			avg=avg/25;
			speedRPM[0] = SPEED_INDEX/avg; // Speed in rpm
			frequency[0]=(int16_t)speedRPM[0];
		}
		EncoderClrFlag(ENCODER_2);
	}
}

void FTM0_IRQHandler(){
	static uint_16 results[10]={0};
	static uint_8 index = 0;
	static uint_16 count = 0;
	if(isEncoderFlagSet(ENCODER_1)){
		count++;
		if(count==LOOP_PULSE){
			count=0;countLoop[1]++;
		}
		
		results[index] = EncoderRead(ENCODER_1);
		index++;
		if(index == 10){
			index = 0;
			FTM0_CNT = 0;		//Clear the counter
			for(uint_8 i=0;i<5;i++){
				avg+=results[i+5]-results[i];
			}
			avg=avg/25;
			speedRPM[1] = SPEED_INDEX/avg; // Speed in rpm
			frequency[1]=(int16_t)speedRPM[1];
		}
		EncoderClrFlag(ENCODER_1);
	}
}


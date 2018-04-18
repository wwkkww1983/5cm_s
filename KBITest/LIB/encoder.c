//===========================================================================
//文件名称：encoder.c
//功能概要：光电编码器驱动源文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-01-27  V1.0
//芯片类型：KEAZ128
//作者：Shine Wong
//===========================================================================
#include "encoder.h"

//==========================================================================
//Function: To initialize a encoder with two PWM ports
//Return: Null
//Arguements: encoderNum: select which encoder to initialize:ENCODER_1, ENCODER_2
//Others: ENCODER_1 uses FTM_0 and ENCODER_2 uses FTM_1 by default
//        PTA0 is used as FTM_0 and PTA1 is used as GPIO function
//        PTC4 is used as FTM_1 and PTC5 is used as GPIO function
//        Interrupt is enabled automatically
//==========================================================================
void initEncoder(uint_8 encoderNum){
	switch(encoderNum){
		case ENCODER_1:
			INCaptureInit(FTM_0,CHANNEL1);
			//configurate PTxx as GPIO port
			gpio_init(directionPort1,GPIO_IN,0);
			//Clear interrupt flag
			FTM0_C1SC &= ~FTM_CnSC_CHF_MASK;
			//enable interrupt
			FTMEnInterrupt(FTM_0);
			break;
		case ENCODER_2:
			INCaptureInit(FTM_1,CHANNEL1);
			//configurate PTxx as GPIO port
			gpio_init(directionPort2,GPIO_IN,0);
			//Clear interrupt flag
			FTM1_C1SC &= ~FTM_CnSC_CHF_MASK;
			//enable interrupt
			FTMEnInterrupt(FTM_1);
			break;
		default:
			break;
	}
}

//==========================================================================
//Function: To clear channel flag(CHF) of the FTMx_CnSC register
//Return: Null
//Arguements: encoderNum: select which encoder to clear:ENCODER_1, ENCODER_2
//Others: ENCODER_1 uses FTM_0 and ENCODER_2 uses FTM_1 by default
//==========================================================================
void EncoderClrFlag(uint_8 encoderNum){
	switch(encoderNum){
		case ENCODER_1:
		    FTM0_C1SC &= ~FTM_CnSC_CHF_MASK;
		    break;
		case ENCODER_2:
		    FTM1_C1SC &= ~FTM_CnSC_CHF_MASK;
		    break;
		default:
			break;
	}
}

//==========================================================================
//Function: To read the frequency of the PWM signal received by the encoder
//Return: return the frequency of the given signal (KHz), if the signal reverses, 
//        the return value will be a negative value
//Arguements: encoderNum: select which encoder to read:ENCODER_1, ENCODER_2
//Others: ENCODER_1 uses FTM_0 and ENCODER_2 uses FTM_1 by default
//        This function reads the COUNT register for ten times and returns 
//        the average frequency of the PWM signal
//==========================================================================
int_16 EncoderRead(uint_8 encoderNum){
	uint_8 direction;
	uint_16 count;
	switch(encoderNum){
		case ENCODER_1:
			count = FTM0_C1V;
			direction = gpio_get(directionPort1);
			break;
		case ENCODER_2:
			count = FTM1_C1V;
			direction = gpio_get(directionPort2);
			break;
		default:
			break;
	}
	//if(direction) return count;
	//if(!direction) return -count;
	return count;
}

//==========================================================================
//Function: to determine whether a encoder's channel interrupt flag(CHF) is set
//Return: returns 0 when the interrupt flag is not set and 1 when set 
//Arguements: encoderNum: select which encoder to read:ENCODER_1, ENCODER_2
//Others: the function is used as the first line of the interrupt server to avoid 
//        unnecessary problems
//==========================================================================
uint_8 isEncoderFlagSet(uint_8 encoderNum){
	switch(encoderNum){
		case ENCODER_1:
			return ((FTM0_C1SC & FTM_CnSC_CHF_MASK) == FTM_CnSC_CHF_MASK);
//			break;
		case ENCODER_2:
			return ((FTM1_C1SC & FTM_CnSC_CHF_MASK) == FTM_CnSC_CHF_MASK);
//			break;
		default:
			return 0;
//			break;
	}
}

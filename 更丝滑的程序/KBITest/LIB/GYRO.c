//===========================================================================
//文件名称：GYRO.h
//功能概要：陀螺仪配置源文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-01-27  V1.0
//芯片类型：KEAZ128
//作者：Shine Wong
//===========================================================================
#include "GYRO.h"

uint_16	gyroMid;

//===========================================================================
//Function: To initialize the Gyroscope module
//Return: Null
//Arguements: Null
//Others: use ADC2(PTA6), ADC3(PTA7), ADC13(F5) as GYRO port
//===========================================================================
void GYROInit(void){
	SIM_SCGC |= SIM_SCGC_ADC_MASK;
	//Enable Port Control function on ADC2, ADC3, ADC13
	//ADC_APCTL1 |=0x200C;
	//Enable FIFO and set the depth to 8
	//ADC_SC4 |= ADC_SC4_AFDEP(7);
	//Use Bus clock
	ADC_SC3 = (ADC_SC3 & ~ADC_SC3_ADICLK_MASK) | ADC_SC3_ADICLK(0x00);
	//set clock divide to 4
	ADC_SC3 = (ADC_SC3 & ~ADC_SC3_ADIV_MASK) | ADC_SC3_ADIV(0x02);
	//select 12 bits conversion mode
	ADC_SC3 |= ADC_SC3_MODE(2);
	//配置ADC_SC2：软件触发，比较功能禁用；默认外部参考电压 VREFH/VREFL
    ADC_SC2 = 0x00;
    //配置ADC_SC1：使能ADC，并设置为连续转换模式,使能外部引脚
    ADC_SC1|= ADC_SC1_ADCO_MASK;
}	

//===========================================================================
//Function: To Read the value converted from the GYRO channel
//Return: return the average of the middle 6 values stored in the FIFO queue
//Arguements: channel: stands for VO1 VO2 VO3 port of the GYRO
//Others: the values are stored in FIFO queue with a depth of 8 by default
//===========================================================================
uint_16 GYRORead(uint_8 channel){
	uint_16 GYROResult[FIFODEPTH]={0},i,result=0;
	//set channel from which ADC reads the values stored
	ADC_SC1 = (ADC_SC1 & ~ADC_SC1_ADCH_MASK) | ADC_SC1_ADCH(channel);
	//wait until the conversion completes
	while(!(ADC_SC1 & ADC_SC1_COCO_MASK));
	//read the results
	for(i=0;i<FIFODEPTH;i++){
		GYROResult[i] = (uint_16)ADC_R;
	}
	//compute the result which is the average of the middle six values of the FIFO queue
	for(i=1;i<FIFODEPTH-1;i++){
		result += GYROResult[i];
	}
	//clear the Conversion complete flag
	ADC_SC1 &= ~ADC_SC1_COCO_MASK;

	return result/(FIFODEPTH-2);
}

//===========================================================================
//Function: To Read the value converted from the GYRO channel for N times
//Return: return the average of the N values obtained from GYRORead()
//Arguements: channel: stands for VO1 VO2 VO3 port of the GYRO
//Others: this function in fact calls GYRORead() for N times and returns the average
//===========================================================================
uint_16 GYROReadn(uint_8 channel,uint_8 N){
	uint_8 i;
	uint_32 result = 0;
	for(i=0;i<N;i++){
		result += GYRORead(channel);
	}
	return (uint_16)(result/N);
}

//===========================================================================
//Function: To solve the datas read from the gyroscope to true angular velocity
//Return: return the angular velocity solved
//Arguements: gyroValue: the primitive value read from the gyroscope
//Others: null
//===========================================================================
float GYROSolve(uint_16 gyroValue){
	float angleVelocity;
	uint_16 realGyro;
	
	realGyro = gyroValue - gyroMid;
	angleVelocity = realGyro*GYRORATIO;
	return angleVelocity;
}

//===========================================================================
//Function: To Read the initial gyroscope value as mid-value
//Return: return mid-value of the gyroscope
//Arguements: channel: stands for VO1 VO2 VO3 port of the GYRO
//Others: call GYROReadn() at the beginning of the programme
//===========================================================================
uint_16 getGyroMid(uint_8 channel){
		gyroMid = GYROReadn(channel,10);
	  return gyroMid;
}

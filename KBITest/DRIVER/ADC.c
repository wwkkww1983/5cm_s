//===========================================================================
//文件名称：ADC.c
//功能概要：ADC模块配置源文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-01-27  V1.0
//芯片类型：KEAZ128
//作者：Shine Wong
//===========================================================================
#include "ADC.h"
//===========================================================================
//Function: To initialize the ADC module
//Return: Null
//Arguements: channel
//Others: use FIFO by default whose depth is 8
//===========================================================================
void ADCInit(void){
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
//Function: To Read the value converted from the ADC channel
//Return: return the average of the middle 6 values stored in the FIFO queue
//Arguements: channel: the channel where the values are read and converted
//                     can be ADC_1 --- ADC_7
//Others: the values are stored in FIFO queue with a depth of 8 by default
//===========================================================================
uint_16 ADCRead(uint_8 channel){
	uint_16 ADCResult[FIFODEPTH]={0},i,result=0;
	//set channel from which ADC reads the values stored
	ADC_SC1 = (ADC_SC1 & ~ADC_SC1_ADCH_MASK) | ADC_SC1_ADCH(channel);
	//wait until the conversion completes
	while(!(ADC_SC1 & ADC_SC1_COCO_MASK));
	//read the results
	for(i=0;i<FIFODEPTH;i++){
		ADCResult[i] = (uint_16)ADC_R;
	}
	//compute the result which is the average of the middle six values of the FIFO queue
	for(i=1;i<FIFODEPTH-1;i++){
		result += ADCResult[i];
	}
	//clear the Conversion complete flag
	ADC_SC1 &= ~ADC_SC1_COCO_MASK;

	return result/(FIFODEPTH-2);
}

//===========================================================================
//Function: To Read the value converted from the ADC channel for N times
//Return: return the average of the N values obtained from ADCRead()
//Arguements: channel: the channel where the values are read and converted
//Others: this function in fact calls ADCRead() for N times and returns the average
//===========================================================================
uint_16 ADCReadn(uint_8 channel,uint_8 N){
	uint_8 i;
	uint_32 result = 0;
	for(i=0;i<N;i++){
		result += ADCRead(channel);
	}
	return (uint_16)(result/N);
}

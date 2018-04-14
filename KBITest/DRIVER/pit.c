/*
 *--------------------------------------------------------------------------------
 *	FileName		pit.h	
 *	Brief			Periodic Interrupt Timer driver
 *	Microchip		KEA128
 *	Author			YTom
 *	E-mail			ybb331082@126.com
 *	ModifyTime		2017.12.12 18:05
 *	Copyright 		2017 TU-Smart. All Rights Reserved.
 *	Attention		PIT use BUS_CLK_KHZ
 *					PIT is working on COUNT_DOWN mode.
 *--------------------------------------------------------------------------------
 */
 
#include "pit.h"

/*
* brief : 	Initialize the PIT module
* param : 	pitchnlx	Select channel (eg.pit_CH0)
			peroid		Set the period in ms
* return:	null
*/
void pitInit_ms(pit_CHType pitchnlx, uint_32 peroid_ms)
{
	SIM_SCGC|=SIM_SCGC_PIT_MASK;  	// Enable PIT clock
    PIT_MCR&=~PIT_MCR_MDIS_MASK;  	// Enable PIT module
	PIT_MCR&=~PIT_MCR_FRZ_MASK;		// Default FRZ setting
	
	pit_IRQSwitch(pitchnlx,Sta_disable);	// NVIC disable PITx interrupt
	PIT_LDVAL(pitchnlx) = peroid_ms*(BUS_CLK_KHZ);	// Set PIT count value
	PIT_TCTRL(pitchnlx) &= ~PIT_TCTRL_CHN_MASK;	// Disable chain mode
	pit_IRQClearFlag(pitchnlx);					// Clear interrupt flag
	PIT_TCTRL(pitchnlx) |= PIT_TCTRL_TIE_MASK;	// Enable PIT interrupt
	pit_IRQSwitch(pitchnlx,Sta_enable);		// NVIC enable PITx interrupt
	
	pit_Switch(pitchnlx,Sta_enable);	// Run PIT
}

/*
* brief : 	Initialize the PIT module
* param : 	pitchnlx	Select channel (eg.pit_CH0)
			peroid		Set the period in us
* return:	null
*/
void pitInit_us(pit_CHType pitchnlx, uint_32 peroid_us)
{
	SIM_SCGC|=SIM_SCGC_PIT_MASK;  	// Enable PIT clock
    PIT_MCR&=~PIT_MCR_MDIS_MASK;  	// Enable PIT module
	PIT_MCR&=~PIT_MCR_FRZ_MASK;		// Default FRZ setting
	
	pit_IRQSwitch(pitchnlx,Sta_disable);	// NVIC disable PITx interrupt
	PIT_LDVAL(pitchnlx) = peroid_us*(BUS_CLK_KHZ/1000);	// Set PIT count value
	PIT_TCTRL(pitchnlx) &= ~PIT_TCTRL_CHN_MASK;	// Disable chain mode
	pit_IRQClearFlag(pitchnlx);					// Clear interrupt flag
	PIT_TCTRL(pitchnlx) |= PIT_TCTRL_TIE_MASK;	// Enable PIT interrupt
	pit_IRQSwitch(pitchnlx,Sta_enable);		// NVIC enable PITx interrupt
	
	pit_Switch(pitchnlx,Sta_enable);	// Run PIT
}

/*
* brief : 	Change PIT state
* param : 	pitchnlx	Select channel (eg.pit_CH0)
			newstate	Select new state (Sta_disable or Sta_Enable)
* return:	null
*/
void pit_Switch(pit_CHType pitchnlx, StatusType newstate)
{
	if(newstate==Sta_disable)
		PIT_TCTRL(pitchnlx)&=~PIT_TCTRL_TEN_MASK;	// Disable PITx
	else
		PIT_TCTRL(pitchnlx)|=PIT_TCTRL_TEN_MASK;	// Enable PITx
}

/*
* brief : 	Change PIT interrupt state with NVIC
* param : 	pitchnlx	Select channel (eg.pit_CH0)
			newstate	Select new state (Sta_disable or Sta_Enable)
* return:	null
*/
void pit_IRQSwitch(pit_CHType pitchnlx, StatusType newstate)
{
	if(newstate==Sta_disable)
		switch(pitchnlx){
			case pit_CH0: NVIC_DisableIRQ(pit_CH0_IRQ); break;
			case pit_CH1: NVIC_DisableIRQ(pit_CH1_IRQ); break;
		}
	else
		switch(pitchnlx){
			case pit_CH0: NVIC_EnableIRQ(pit_CH0_IRQ); break;
			case pit_CH1: NVIC_EnableIRQ(pit_CH1_IRQ); break;
		}
}

/*
* brief : 	Get PIT interrupt flag
* param : 	pitchnlx	Select channel (eg.pit_CH0)
* return:	PIT interrupt flag state
*/
uint_8 pit_IRQGetFlag(pit_CHType pitchnlx)
{
	return (PIT_TFLG(pitchnlx)&PIT_TFLG_TIF_MASK);	// Return interrupt flag
}

/*
* brief : 	Clear PIT interrupt flag
* param : 	pitchnlx	Select channel (eg.pit_CH0)
* return:	null
*/
void pit_IRQClearFlag(pit_CHType pitchnlx)
{
	PIT_TFLG(pitchnlx)|=PIT_TFLG_TIF_MASK;		// Clear interrupt flag
}




/*-------------------------------INNER FUNCTIONS-------------------------------*/

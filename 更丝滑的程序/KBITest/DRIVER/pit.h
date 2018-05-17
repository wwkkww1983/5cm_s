/*
 *--------------------------------------------------------------------------------
 *	FileName		pit.h	
 *	Brief			Periodic Interrupt Timer driver header
 *	Microchip		KEA128
 *	Author			YTom
 *	E-mail			ybb331082@126.com
 *	ModifyTime		2017.12.12 18:05
 *	Copyright 		2017 TU-Smart. All Rights Reserved.
 *	Info			(IRQn_Type)PIT_CH0_IRQn = 22
 *					(IRQn_Type)PIT_CH1_IRQn = 23
 *					
 *--------------------------------------------------------------------------------
 */

#ifndef PIT_H_
#define PIT_H_

#include "common.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/* Channels interrupt number */
#define pit_CH0_IRQ 	PIT_CH0_IRQn
#define pit_CH1_IRQ 	PIT_CH1_IRQn
	
/* Channels offset */
typedef enum{
	pit_CH0=0,
	pit_CH1=1
} pit_CHType;

/* PIT interrupt flag */
#define pit_IRQFlagged 		1

/*
* brief : 	Initialize the PIT module
* param : 	pitchnlx	Select channel (eg.pit_CH0)
			peroid		Set the period in ms,us
* return:	null
*/
void pitInit_ms(pit_CHType pitchnlx, uint_32 peroid_ms);
void pitInit_us(pit_CHType pitchnlx, uint_32 peroid_us);
/*
* brief : 	Change PIT state
* param : 	pitchnlx	Select channel (eg.pit_CH0)
			newstate	Select new state (Sta_disable or Sta_Enable)
* return:	null
*/
void pit_Switch(pit_CHType pitchnlx, StatusType newstate);

/*
* brief : 	Change PIT interrupt state with NVIC
* param : 	pitchnlx	Select channel (eg.pit_CH0)
			newstate	Select new state (Sta_disable or Sta_Enable)
* return:	null
*/
void pit_IRQSwitch(pit_CHType pitchnlx, StatusType newstate);

/*
* brief : 	Get PIT interrupt flag
* param : 	pitchnlx	Select channel (eg.pit_CH0)
* return:	PIT interrupt flag state
*/
uint_8 pit_IRQGetFlag(pit_CHType pitchnlx);

/*
* brief : 	Clear PIT interrupt flag
* param : 	pitchnlx	Select channel (eg.pit_CH0)
* return:	null
*/
void pit_IRQClearFlag(pit_CHType pitchnlx);


#ifdef  __cplusplus
}
#endif

#endif 		//PIT_H_

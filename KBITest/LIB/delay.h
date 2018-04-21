/*
 *--------------------------------------------------------------------------------
 *	FileName		delay.h	
 *	Brief			
 *	Microchip		KEA128
 *	Author			YTom
 *	E-mail			ybb331082@126.com
 *	ModifyTime		
 *	Copyright 		2017 TU-Smart. All Rights Reserved.
 *	Info			
 *--------------------------------------------------------------------------------
 */

#ifndef DELAY_H_
#define DELAY_H_

#include "common.h"

#ifdef  __cplusplus
extern "C"
{
#endif
	
#define DELAY_CLK	BUS_CLK_KHZ

typedef enum{
	delay_CORE_CLK16	= 0,
	delay_CORE_CLK		= 1
} delay_ClockSource;


/*
* brief : 	Initialize systick for delay
* param : 	clksrc	Choose clock source
				systick_CORE_CLK = 48MHz, systick_CORE_CLK16=systick_CORE_CLK / 16 = 3MHz
			per_us	Set reload time
* return:	
* note	:	
*/
void delay_Init(delay_ClockSource clksrc);

/*
* brief : 	Delay sometime
* param : 	ms		Delay time
*			us		Delay time
*/
void delay_ms(uint_16 ms);
void delay_us(uint_32 us);


#ifdef  __cplusplus
}
#endif

#endif 		//DELAY_H_

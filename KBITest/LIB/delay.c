/*
 *--------------------------------------------------------------------------------
 *	FileName		delay.c	
 *	Brief			
 *	Microchip		KEA128
 *	Author			YTom
 *	E-mail			ybb331082@126.com
 *	ModifyTime		18-01-30,19:52
 *	Copyright 		2017 TU-Smart. All Rights Reserved.
 *	Attention	
 *--------------------------------------------------------------------------------
 */
 
#include "delay.h"

uint_32 delay_tmp; 

/*
* brief : 	Initialize systick for delay
* param : 	clksrc	Choose clock source
				delay_CORE_CLK = 48MHz, delay_CORE_CLK16=systick_CORE_CLK / 16 = 3MHz
			per_us	Set reload time
* return:	
* note	:	For initializing, reload value is set as 0, and it don't enable the systick;
*/
void delay_Init(delay_ClockSource clksrc)
{
	SysTick->CTRL = 0;   // Reset systick
	SysTick->VAL  = 0;   // Clear count
    // Set reload value
    if(clksrc==delay_CORE_CLK16) {
		SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;	// Set clock source as CORE_CLK/16
    	SysTick->LOAD = DELAY_CLK*0/16;
     }
    else {		// Default clock source
		SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;	// Set clock source as CORE_CLK
    	SysTick->LOAD = DELAY_CLK*0;
    }
    // Set SysTick priority as 2
    NVIC_SetPriority(SysTick_IRQn, 2);
//	SCB->SHP[1] |= (uint_32)(0x02)<<30;

    //设置时钟源,允许中断,使能该模块,开始计数
// 	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;			// Count to 0 with interrupt
//	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;			// Enable systick
}

/*
* brief : 	Delay sometime
* param : 	ms		Delay time
*			us		Delay time
* note	:	Choose proper value (not too big)
*			Trial passed: 1 000ms and 1 000 000us
*/
void delay_ms(uint_16 ms)
{
	if(SysTick->CTRL&SysTick_CTRL_CLKSOURCE_Msk)
		SysTick->LOAD = DELAY_CLK*ms; 					// Load time
	else
		SysTick->LOAD = DELAY_CLK*ms/16; 				// Load time
	SysTick->VAL = 0x00;        						// Clear count
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;			// Start timing
	do {
		delay_tmp = SysTick->CALIB;							// Waiting
	} while((delay_tmp&SysTick_CTRL_ENABLE_Msk)&&!(delay_tmp&SysTick_CTRL_COUNTFLAG_Msk));
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk; 			// Close systick
	SysTick->VAL = 0x00;       							// Clear count
}
void delay_us(uint_32 us)
{
	
	if(SysTick->CTRL&SysTick_CTRL_CLKSOURCE_Msk)
		SysTick->LOAD = DELAY_CLK*us/1000; 				// Load time
	else
		SysTick->LOAD = DELAY_CLK*us/16000;				// Load time
	SysTick->VAL = 0x00;        						// Clear count
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;			// Start timing
	do {
		delay_tmp = SysTick->CALIB;							// Waiting
	} while((delay_tmp&SysTick_CTRL_ENABLE_Msk)&&!(delay_tmp&SysTick_CTRL_COUNTFLAG_Msk));
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk; 			// Close systick
	SysTick->VAL = 0x00;       							// Clear count
}

/*
* brief : 	PIT Channel 0 interrupt function
* param : 	null
* return:	null
* note	:	
*/
//void SysTick_Handler(void)
//{
//}

/*-------------------------------INNER FUNCTIONS-------------------------------*/

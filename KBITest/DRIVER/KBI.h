//===========================================================================
//文件名称：KBI.h
//功能概要：KBI键盘中断模块配置头文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-03-04  V1.0
//芯片类型：KEAZ128
//作者：Shine Wong
//===========================================================================
#ifndef KBI_H_
#define KBI_H_

#include "gpio.h"

/*KBI 与 PORT 引脚对照表
#define KBI0_0  (PORTA|(0))
#define KBI0_1  (PORTA|(1))
#define KBI0_2  (PORTA|(2))
#define KBI0_3  (PORTA|(3))
#define KBI0_4  (PORTA|(4))
#define KBI0_5  (PORTA|(5))
#define KBI0_6  (PORTA|(6))
#define KBI0_7  (PORTA|(7))

#define KBI0_8  (PORTB|(0))
#define KBI0_9  (PORTB|(1))
#define KBI0_10 (PORTB|(2))
#define KBI0_11 (PORTB|(3))
#define KBI0_12 (PORTB|(4))
#define KBI0_13 (PORTB|(5))
#define KBI0_14 (PORTB|(6))
#define KBI0_15 (PORTB|(7))

#define KBI0_16 (PORTC|(0))
#define KBI0_17 (PORTC|(1))
#define KBI0_18 (PORTC|(2))
#define KBI0_19 (PORTC|(3))
#define KBI0_20 (PORTC|(4))
#define KBI0_21 (PORTC|(5))
#define KBI0_22 (PORTC|(6))
#define KBI0_23 (PORTC|(7))

#define KBI0_24 (PORTD|(0))
#define KBI0_25 (PORTD|(1))
#define KBI0_26 (PORTD|(2))
#define KBI0_27 (PORTD|(3))
#define KBI0_28 (PORTD|(4))
#define KBI0_29 (PORTD|(5))
#define KBI0_30 (PORTD|(6))
#define KBI0_31 (PORTD|(7))

#define KBI1_0  (PORTE|(0))
#define KBI1_1  (PORTE|(1))
#define KBI1_2  (PORTE|(2))
#define KBI1_3  (PORTE|(3))
#define KBI1_4  (PORTE|(4))
#define KBI1_5  (PORTE|(5))
#define KBI1_6  (PORTE|(6))
#define KBI1_7  (PORTE|(7))

#define KBI1_8  (PORTF|(0))
#define KBI1_9  (PORTF|(1))
#define KBI1_10 (PORTF|(2))
#define KBI1_11 (PORTF|(3))
#define KBI1_12 (PORTF|(4))
#define KBI1_13 (PORTF|(5))
#define KBI1_14 (PORTF|(6))
#define KBI1_15 (PORTF|(7))

#define KBI1_16 (PORTG|(0))
#define KBI1_17 (PORTG|(1))
#define KBI1_18 (PORTG|(2))
#define KBI1_19 (PORTG|(3))
#define KBI1_20 (PORTG|(4))
#define KBI1_21 (PORTG|(5))
#define KBI1_22 (PORTG|(6))
#define KBI1_23 (PORTG|(7))

#define KBI1_24 (PORTH|(0))
#define KBI1_25 (PORTH|(1))
#define KBI1_26 (PORTH|(2))
#define KBI1_27 (PORTH|(3))
#define KBI1_28 (PORTH|(4))
#define KBI1_29 (PORTH|(5))
#define KBI1_30 (PORTH|(6))
#define KBI1_31 (PORTH|(7))
*/

#define KBI_0 (0<<8)
#define KBI_1 (1<<8)

#define FALLING 0
#define RISING  1

#define KBI0_IRQ_NO 24
#define KBI1_IRQ_NO 25

//===========================================================================
//Function: To initialize KBI module and select the approprite edge as well
//          as whether you are going to use pullup resistor
//Return: None
//Arguements: KBIPort: should be given in form 'KBINum|port' e.g.KBI_0|(0)
//            edge: select the falling edge(FALLING) or rising edge(RISING) 
//            pullSelect: choose whether to enable pullup resistor(1) or not(0)
//Others: None
//===========================================================================
void KBIInit(uint_16 KBIPort, uint_8 edge, uint_8 pullSelect);

//===========================================================================
//Function: To clear the interrupt flag as well as the KBIx_SP field
//Return: None
//Arguements: KBINum: select KBI_0 or KBI_1
//Others: This function should be used in the interrupt handler function
//===========================================================================
void KBIClear(uint_16 KBINum);

//===========================================================================
//Function: To detect whether KBI flag is set
//Return: True when the interrupt flag is set
//Arguements: KBINum: select KBI_0 or KBI_1
//Others: This function should be used in the interrupt handler function
//===========================================================================
uint_8 isKBIFlagSet(uint_16 KBINum);

#endif

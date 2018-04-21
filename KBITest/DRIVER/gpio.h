//===========================================================================
//文件名称：gpio.h
//功能概要：GPIO底层驱动构件头文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-01-28  V1.0
//芯片类型：KEA128
//作者： Shine Wong
//===========================================================================

#ifndef GPIO_H        //防止重复定义（GPIO_H  开头)
#define GPIO_H

#include "common.h"   //包含公共要素头文件

// 端口号地址偏移量宏定义
#define PORTA    (0<<8)				//0000 0000 0000 0000
#define PORTB    (1<<8)				//0000 0001 0000 0000
#define PORTC    (2<<8)				//0000 0010 0000 0000
#define PORTD    (3<<8)				//0000 0011 0000 0000
#define PORTE    (4<<8)				//0000 0100 0000 0000
#define PORTF    (5<<8)				//0000 0101 0000 0000
#define PORTG    (6<<8)				//0000 0110 0000 0000   
#define PORTH    (7<<8)				//0000 0111 0000 0000
#define PORTI    (8<<8)				//0000 1000 0000 0000
#define PinMask 	((uint16)0x00ff)
//引脚方向宏定义
#define GPIO_IN      0
#define GPIO_OUTPUT  1

//===========================================================================
//函数名称：gpio_init
//函数返回：无
//参数说明：port_pin：(端口号)|(引脚号)（例：PORTB|(5) 表示为B口5号脚）
//       dir：引脚方向（0=输入，1=输出,可用引脚方向宏定义）
//       state：端口引脚初始状态（0=低电平，1=高电平）
//功能概要：初始化指定端口引脚作为GPIO引脚功能，并定义为输入或输出，若是输出，
//       还指定初始状态是低电平或高电平
//===========================================================================
void gpio_init(uint_16 port_pin, uint_8 dir, uint_8 state);

//===========================================================================
//函数名称：gpio_set
//函数返回：无
//参数说明：port_pin：(端口号)|(引脚号)（例：PORTB|(5) 表示为B口5号脚）
//       state：希望设置的端口引脚状态（0=低电平，1=高电平）
//功能概要：当指定端口引脚被定义为GPIO功能且为输出时，本函数设定引脚状态
//===========================================================================
void gpio_set(uint_16 port_pin, uint_8 state);

//===========================================================================
//函数名称：gpio_get
//函数返回：指定端口引脚的状态（1或0）
//参数说明：port_pin：(端口号)|(引脚号)（例：PORTB|(5) 表示为B口5号脚）
//功能概要：当指定端口引脚被定义为GPIO功能且为输入时，本函数获取指定引脚状态
//===========================================================================
uint_8 gpio_get(uint_16 port_pin);

//===========================================================================
//函数名称：gpio_reverse
//函数返回：无
//参数说明：port_pin：(端口号)|(引脚号)（例：PORTB|(5) 表示为B口5号脚）
//功能概要：当指定端口引脚被定义为GPIO功能且为输出时，本函数反转引脚状态
//===========================================================================
void gpio_reverse(uint_16 port_pin);

//===========================================================================
//函数名称：gpio_pull
//函数返回：无
//参数说明：port_pin：端口号|引脚号（例：PORTB|(5) 表示为B口5号脚）
//          pullselect：引脚上拉使能选择（ 0=上拉除能，1=上拉使能）
//功能概要：使指定引脚上拉高电平
//===========================================================================
void gpio_pull(uint_16 port_pin, uint_8 pullselect);

void gpio_setOut(uint_16 port_pin);
void gpio_setIn(uint_16 port_pin);

#endif     //防止重复定义（GPIO_H  结尾)


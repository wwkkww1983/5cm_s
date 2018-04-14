﻿//===========================================================================
//文件名称：common.h
//功能概要：公共要素头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版本更新：2015-06-05  V2.0
//芯片类型：KEA128
//===========================================================================

#ifndef	__COMMON_H       //防止重复定义（_COMMON_H  开头)
#define __COMMON_H

// 1．芯片寄存器映射文件及处理器内核属性文件
#include "core_cmFunc.h"
#include "core_cmInstr.h"
#include "core_cm0plus.h"
#include "SKEAZ1284.h"           // 包含芯片头文件
#include "system_SKEAZ1284.h"    // 包含芯片系统初始化文件

#define  SYSTEM_CLK_KHZ   DEFAULT_SYSTEM_CLOCK/1000// 芯片系统时钟频率(KHz)
#define  CORE_CLK_KHZ     SYSTEM_CLK_KHZ           // 芯片内核时钟频率(KHz)
#define  BUS_CLK_KHZ      SYSTEM_CLK_KHZ/2         // 芯片总线时钟频率(KHz)

// 2．定义开关总中断
#define ENABLE_INTERRUPTS   __enable_irq   // 开总中断
#define DISABLE_INTERRUPTS  __disable_irq  // 关总中断

// 3．位操作宏函数（置位、清位、获得寄存器一位的状态）
#define BSET(bit,Register)  ((Register)|= (1<<(bit)))    // 置寄存器的一位
#define BCLR(bit,Register)  ((Register) &= ~(1<<(bit)))  // 清寄存器的一位
#define BGET(bit,Register)  (((Register) >> (bit)) & 1)  // 获得寄存器一位的状态

// 4．重定义基本数据类型（类型别名宏定义）
typedef unsigned char uint_8;   // 无符号8位数，字节
typedef unsigned short int uint_16;  // 无符号16位数，字
typedef unsigned long int uint_32;  // 无符号32位数，长字
typedef char int_8;    // 有符号8位数
typedef short int int_16;   // 有符号16位数
typedef int int_32;   // 有符号32位数
// 不优化类型
typedef volatile uint_8 vuint_8;  // 不优化无符号8位数，字节
typedef volatile uint_16 vuint_16; // 不优化无符号16位数，字
typedef volatile uint_32 vuint_32; // 不优化无符号32位数，长字
typedef volatile int_8 vint_8;   // 不优化有符号8位数
typedef volatile int_16 vint_16;  // 不优化有符号16位数
typedef volatile int_32 vint_32;  // 不优化有符号32位数

#endif       //防止重复定义（_COMMON_H结尾)

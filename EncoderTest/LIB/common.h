//===========================================================================
//文件名称：common.h
//功能概要：公共要素头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2014-12-10  V1.0
//芯片类型：KEA128
//===========================================================================

#ifndef	__COMMON_H       //防止重复定义（_COMMON_H  开头)
#define __COMMON_H

//1．芯片寄存器映射文件及处理器内核属性文件
#include "SKEAZ1284.h"      // 包含芯片头文件
//2．定义开关总中断
#ifndef __enable_irq
	#define __enable_irq __asm(" CPSIE i");
#endif

 /* Macro to disable all interrupts. */
#ifndef __disable_irq
	#define __disable_irq __asm(" CPSID i");
#endif

#define ARM_INTERRUPT_LEVEL_BITS   2       //MQX操作系统使用

//4．重定义基本数据类型（类型别名宏定义）
typedef unsigned char        uint_8;   // 无符号8位数，字节
typedef unsigned short int   uint_16;  // 无符号16位数，字
typedef unsigned long int    uint_32;  // 无符号32位数，长字
typedef char                 int_8;    // 有符号8位数
typedef short int            int_16;   // 有符号16位数
typedef int                  int_32;   // 有符号32位数
//不优化类型
typedef volatile uint_8      vuint_8;  // 不优化无符号8位数，字节
typedef volatile uint_16     vuint_16; // 不优化无符号16位数，字
typedef volatile uint_32     vuint_32; // 不优化无符号32位数，长字
typedef volatile int_8       vint_8;   // 不优化有符号8位数
typedef volatile int_16      vint_16;  // 不优化有符号16位数
typedef volatile int_32      vint_32;  // 不优化有符号32位数

typedef enum{
	Sta_disable = 0,
	Sta_enable  = 1
} StatusType;

#define SYSTEM_CLK_KHZ   	(SystemCoreClock)/1000	// Microchip system clock frequency(KHz).
#define CORE_CLK_KHZ     	SYSTEM_CLK_KHZ          // Microchip core frequency(KHz)
#define BUS_CLK_KHZ      	SYSTEM_CLK_KHZ/2        // Microchip bus clock frequency(KHz)

// Define the global interrupts switch.
#define ENABLE_INTERRUPTS   __enable_irq   // Open all interrupts.
#define DISABLE_INTERRUPTS  __disable_irq  // Close all interrupts.

// Bit-operating macro functions.
#define BSET(bit,Register)  ((Register)|= (1<<(bit)))    // Set bit.
#define BCLR(bit,Register)  ((Register) &= ~(1<<(bit)))  // Reset bit.
#define BGET(bit,Register)  (((Register) >> (bit)) & 1)  // Get bit status.


// 5．临界区访问函数

//=========================================================================
//函数名称：init_critical
//参数说明：无
//函数返回：无
//功能概要：初始化临界区访问控制
//=========================================================================
void  init_critical(void);

//=========================================================================
//函数名称：enter_critical
//参数说明：无
//函数返回：无
//功能概要：进入临界区
//=========================================================================
void  enter_critical(void);

//=========================================================================
//函数名称：exit_critical
//参数说明：无
//函数返回：无
//功能概要：离开临界区
//=========================================================================
void  exit_critical(void);


//============================================================================
//函数名称：enable_irq
//函数返回：无  
//参数说明：irq：irq号
//功能概要：使能irq中断 
//============================================================================
void enable_irq (uint_16 irq);

//============================================================================
//函数名称：disable_irq
//函数返回：无      
//参数说明：irq：irq号
//功能概要：禁止irq中断 
//============================================================================
void disable_irq (uint_16 irq);

//============================================================================
//函数名称：set_irq_priority
//函数返回：无      
//参数说明：irq：irq号         											   
//          prio：优先级
//功能概要：设置irq中断和优先级 
//============================================================================
void set_irq_priority (uint_16 irq, uint_16 prio);

#endif       //防止重复定义（_COMMON_H结尾)

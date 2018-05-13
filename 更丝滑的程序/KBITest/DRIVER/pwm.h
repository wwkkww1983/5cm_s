//===========================================================================
//文件名称：pwm.h
//功能概要：pwm底层驱动构件源文件
//版权所有：同济大学Tu_smart智能车队	
//版本更新：2018-01-23  V1.0
//芯片类型：KEAZ128
//作者：Shine Wong
//===========================================================================
#include "common.h"   //包含公共要素头文件

#ifndef FTM_H_
#define FTM_H_

//FTM模块号
#define FTM_0 0
#define FTM_1 1
#define FTM_2 2

//通道号，FTM0和FTM1：通道0~通道1，FTM2：通道0~通道5
#define CHANNEL0 0
#define CHANNEL1 1
#define CHANNEL2 2
#define CHANNEL3 3
#define CHANNEL4 4
#define CHANNEL5 5


//FTM2通道0引脚组: 1=PTC0脚, 2=PTH0脚, 3=PTF0脚
#define FTM2_CHANNEL0_GROUP 2    //KEA128板上使用PTH0脚

//FTM2通道1引脚组: 1=PTC1脚, 2=PTH1脚, 3=PTF1脚
#define FTM2_CHANNEL1_GROUP 2	 //KEA128板上使用PTH1脚

//FTM2通道2引脚组: 1=PTC2脚, 2=PTD0脚, 3=PTG4脚
#define FTM2_CHANNEL2_GROUP 3	 //KEA128板上使用PTG4脚

//FTM2通道3引脚组: 1=PTC3脚, 2=PTD1脚, 3=PTG5脚
#define FTM2_CHANNEL3_GROUP 3	 //KEA128板上使用PTG5脚

//============================================================================
//函数名称：FTM_PWM_init
//函数返回：无
//参数说明：ftmNo:FTM模块号：FTM_0、FTM_1、FTM_2
//          channel:选择通道号：FTM0和FTM1：通道0、通道1
//                             FTM2:通道0、1、2、3、4、5
//          freq：设置PWM的频率，单位为KHz。取值从0.012到1500
//          duty：占空比：精度取决于设置的freq值，精度为freq/1500。
//功能概要：初始化PWM模块
//============================================================================
void FTM_PWM_init(uint_8 ftmNo,uint_8 channel, float freq, float duty);


//============================================================================
//函数名称：FTM_PWM_set_duty
//函数返回：无
//参数说明：ftmNo:FTM模块号：FTM_0、FTM_1、FTM_2
//          channel:选择通道号：FTM0和FTM1：通道0、通道1
//                             FTM2:通道0、1、2、3、4、5
//          duty：占空比：精度取决于设置的mod值，精度为1/mod。
//功能概要：初始化PWM模块
//============================================================================
void FTM_PWM_set_duty(uint_8 ftmNo, uint_8 channel, float duty);

#endif

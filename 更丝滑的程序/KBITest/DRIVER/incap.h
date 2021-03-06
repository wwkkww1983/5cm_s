//===========================================================================
//文件名称：incap.h
//功能概要：输出捕捉底层驱动构件源文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-01-27  V1.0
//芯片类型：KEA128
//作者    :Shine Wong
//===========================================================================
#include "common.h"   //包含公共要素头文件

#ifndef FTM_H_
#define FTM_H_

//FTM模块号
#define FTM_0 0
#define FTM_1 1

#define FTM0_irq_no 17
#define FTM1_irq_no 18

//通道号，FTM0和FTM1：通道0~通道1
#define CHANNEL0 0
#define CHANNEL1 1

//输入捕获时钟频率
#define INCAP_CLOCK		375000

//------------------------------FTM0通道和引脚选择----------------------
//注：通过展开以下宏定义并修改宏定义值可选择通道号和引脚

//FTM0通道0引脚组: 1=PTA0脚，2=PTB2脚
//#define FTM0_CHANNEL0_GROUP 1

//FTM0通道1引脚组: 1=PTA1脚，2=PTB3脚
#define FTM0_CHANNEL1_GROUP 1
//----------------------------------------------------------------------


//------------------------------FTM1通道和引脚选择----------------------
//注：通过展开以下宏定义并修改宏定义值可选择通道号和引脚

//FTM1通道0引脚组: 1=PTC4脚，2=PTH2脚
//#define FTM1_CHANNEL0_GROUP 1

//FTM1通道1引脚组: 1=PTC5脚, 2=PTE7脚
#define FTM1_CHANNEL1_GROUP 1
//----------------------------------------------------------------------

//============================================================================
//函数名称：FTM_INCaptureInit
//函数返回：无
//参数说明：ftmNo:FTM模块号：FTM_0、FTM_1、FTM_2
//          channel:选择通道号：FTM0和FTM1：通道0、通道1
//                             FTM2:通道0、1、2、3、4、5
//功能概要：初始化输入捕捉模块
//============================================================================
void INCaptureInit(uint_8 ftmNo,uint_8 channel);

//====================================================================
//函数名称：enable_ftm_int
//函数返回：无
//参数说明：FTMChannel:FTM通道号
//功能概要：开ftm中断
//====================================================================
void FTMEnInterrupt( uint_8 FTMChannel);

//====================================================================
//函数名称：disable_ftm_int
//函数返回：无
//参数说明：FTMChannel:FTM通道号
//功能概要：关ftm中断
//====================================================================
void FTMdisInterrupt(uint_8 FTMChannel);


#endif /* FTM_H_ */

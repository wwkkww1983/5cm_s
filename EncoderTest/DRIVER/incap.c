//===========================================================================
//文件名称：incap.h
//功能概要：输出捕捉底层驱动构件源文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-01-27  V1.0
//芯片类型：KEA128
//作者    :Shine Wong
//===========================================================================
#include "incap.h"

//FTM0、FTM1、FTM2地址映射
FTM_MemMapPtr FTM_ARR2[]={FTM0_BASE_PTR,FTM1_BASE_PTR,FTM2_BASE_PTR};

//============================================================================
//函数名称：FTM_INCaptureInit
//参数说明：ftmNo:FTM模块号：FTM_0、FTM_1
//          channel:选择通道号：FTM0和FTM1：通道0、通道1
 //功能概要：初始化输入捕捉模块
//============================================================================
void INCaptureInit(uint_8 ftmNo,uint_8 channel)
{
	//防止越界
	if(ftmNo>2) ftmNo=2;
	switch(ftmNo)
	{
		case FTM_0:

			#if(FTM0_CHANNEL0_GROUP==1)
				//复用引脚PTA0为FTM0通道0功能
				SIM_PINSEL0 &= ~SIM_PINSEL_FTM0PS0_MASK;
			#endif

			#if(FTM0_CHANNEL0_GROUP==2)
				//复用引脚PTB2为FTM0通道0功能
				SIM_PINSEL0 |= SIM_PINSEL_FTM0PS0_MASK;
			#endif

			#if(FTM0_CHANNEL1_GROUP==1)
				//复用引脚PTA1为FTM0通道1功能
				SIM_PINSEL0 &= ~SIM_PINSEL_FTM0PS1_MASK;
			#endif

			#if(FTM0_CHANNEL1_GROUP==2)
				//复用引脚PTB3为FTM0通道1功能
				SIM_PINSEL0 |= SIM_PINSEL_FTM0PS1_MASK;
			#endif

			//使能FTM0的总线时钟
			SIM_SCGC |= SIM_SCGC_FTM0_MASK;
			break;

		case FTM_1:
			#if(FTM1_CHANNEL0_GROUP==1)
				//复用引脚PTC4为FTM1通道0功能
				SIM_PINSEL0 &= ~SIM_PINSEL_FTM1PS0_MASK;
			#endif

			#if(FTM1_CHANNEL0_GROUP==2)
				//复用引脚PTH2为FTM1通道0功能
				SIM_PINSEL0 |= SIM_PINSEL_FTM1PS0_MASK;
			#endif

			#if(FTM1_CHANNEL1_GROUP==1)
				//复用引脚PTC5为FTM1通道1功能
				SIM_PINSEL0 &= ~SIM_PINSEL_FTM1PS1_MASK;
			#endif

			#if(FTM1_CHANNEL1_GROUP==2)
				//复用引脚PTE7为FTM1通道1功能
				SIM_PINSEL0 |= SIM_PINSEL_FTM1PS1_MASK;
			#endif

			//使能FTM1的总线时钟
			SIM_SCGC |= SIM_SCGC_FTM1_MASK;
			break;
	}
    //总线时钟频率24MHz,分频因子128/2,分频后为187.5*2KHz
    FTM_SC_REG(FTM_ARR2[ftmNo]) |= FTM_SC_PS(6);
    //计数器清零
    FTM_CNT_REG(FTM_ARR2[ftmNo])=0;
    //为了保证捕捉信号时不被定时器溢出中断打断，需将MOD值尽可能设置大一点
    FTM_MOD_REG(FTM_ARR2[ftmNo])=65535;
    
    //设置为上升沿捕捉
    FTM_CnSC_REG(FTM_ARR2[ftmNo],channel) &=~FTM_CnSC_MSA_MASK;
    FTM_CnSC_REG(FTM_ARR2[ftmNo],channel) &=~FTM_CnSC_MSB_MASK;
    FTM_CnSC_REG(FTM_ARR2[ftmNo],channel) &=~FTM_CnSC_ELSB_MASK;
    FTM_CnSC_REG(FTM_ARR2[ftmNo],channel) |=FTM_CnSC_ELSA_MASK;
    //channel中断使能
    FTM_CnSC_REG(FTM_ARR2[ftmNo],channel) |=FTM_CnSC_CHIE_MASK;

    //使用系统时钟
    FTM_SC_REG(FTM_ARR2[ftmNo]) |= FTM_SC_CLKS(1);
}

//====================================================================
//函数名称：enable_ftm_int
//函数返回：无
//参数说明：FTMChannel:FTM模块通道
//功能概要：开ftm中断
//====================================================================
void FTMEnInterrupt(uint_8 FTMChannel)
{
    //开FTM中断
    NVIC_EnableIRQ(FTM0_irq_no + FTMChannel);
}

//====================================================================
//函数名称：disable_ftm_int
//函数返回：无
//参数说明：FTMChannel:FTM通道号
//功能概要：关ftm中断
//====================================================================
void FTMdisInterrupt(uint_8 FTMChannel)
{
    //关FTM中断
    NVIC_DisableIRQ(FTM0_irq_no + FTMChannel);
}

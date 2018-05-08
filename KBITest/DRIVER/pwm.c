//===========================================================================
//文件名称：pwm.c
//功能概要：pwm底层驱动构件源文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-01-23  V1.0
//芯片类型：KEAZ128
//作者：Shine Wong
//===========================================================================
#include "pwm.h"

//FTM0、FTM1、FTM2地址映射
const FTM_MemMapPtr FTM_ARR[]={FTM0_BASE_PTR,FTM1_BASE_PTR,FTM2_BASE_PTR};

static uint_16 MOD_VALUE;

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
void FTM_PWM_init(uint_8 ftmNo,uint_8 channel, float freq, float duty)
{
	uint_16 duty_channel;
	uint_16 mod;

	//防止模块号越界
		if(ftmNo>2) ftmNo=2;

	//计算mod值，周期（ms) = MOD / 1500
	if(freq <= 0.012)
		mod = 0xFFFF;
	else if(freq>1500)
		mod=0;
	else
		mod = 1500 / freq;

	//防止周期越界
	if(duty > 100)
		duty = 100;
	if(duty < 0)
		duty = 0;

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

		case FTM_2:
			#if(FTM2_CHANNEL0_GROUP==1)
				//复用引脚PTC0为FTM2通道0功能
				SIM_PINSEL1 &= ~SIM_PINSEL1_FTM2PS0_MASK;
			#endif

			#if(FTM2_CHANNEL0_GROUP==2)
				//复用引脚PTH0为FTM2通道0功能
				SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS0(1);
			#endif

			#if(FTM2_CHANNEL0_GROUP==3)
				//复用引脚PTF0为FTM2通道0功能
				SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS0(2);
			#endif

			#if(FTM2_CHANNEL1_GROUP==1)
				//复用引脚PTC1为FTM2通道1功能
				SIM_PINSEL1 &= ~SIM_PINSEL1_FTM2PS1_MASK;
			#endif

			#if(FTM2_CHANNEL1_GROUP==2)
				//复用引脚PTH1为FTM2通道1功能
				SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS1(1);
		        #endif
  
		        #if(FTM2_CHANNEL1_GROUP==3)
			        //复用引脚PTF1为FTM2通道1功能
			        SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS1(2);
	                #endif

            #if(FTM2_CHANNEL2_GROUP==1)
				//复用引脚PTC2为FTM2通道2功能
				SIM_PINSEL1 &= ~SIM_PINSEL1_FTM2PS2_MASK;
			#endif

			#if(FTM2_CHANNEL2_GROUP==2)
				//复用引脚PTD0为FTM2通道2功能
				SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS2(1);
		        #endif

		        #if(FTM2_CHANNEL2_GROUP==3)
			       //复用引脚PTG4为FTM2通道2功能
			       SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS2(2);
	                #endif


			#if(FTM2_CHANNEL3_GROUP==1)
				//复用引脚PTC3为FTM2通道3功能
				SIM_PINSEL1 &= ~SIM_PINSEL1_FTM2PS3_MASK;
			#endif

			#if(FTM2_CHANNEL3_GROUP==2)
				//复用引脚PTD1为FTM2通道3功能
				SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS3(1);
			#endif

			#if(FTM2_CHANNEL3_GROUP==3)
			   //复用引脚PTG5为FTM2通道3功能
			   SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS3(2);
			#endif

			#if(FTM2_CHANNEL4_GROUP==1)
				//复用引脚PTB4为FTM2通道4功能
				SIM_PINSEL1 &= ~SIM_PINSEL1_FTM2PS4_MASK;
			#endif

			#if(FTM2_CHANNEL4_GROUP==2)
				//复用引脚PTG6为FTM2通道4功能
				SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS4_MASK;
			#endif

			#if(FTM2_CHANNEL5_GROUP==1)
				//复用引脚PTB5为FTM2通道5功能
				SIM_PINSEL1 &= ~SIM_PINSEL1_FTM2PS5_MASK;
			#endif

			#if(FTM2_CHANNEL5_GROUP==2)
				//复用引脚PTG7为FTM2通道5功能
				SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS5_MASK;
			#endif

			//使能FTM2的总线时钟
			SIM_SCGC |= SIM_SCGC_FTM2_MASK;
			break;
	}

    //写保护禁止
    FTM_ARR[ftmNo]->MODE |= FTM_MODE_WPDIS_MASK;
    //总线时钟频率24MHz,分频因子16,分频后为1.5MHz
    FTM_ARR[ftmNo]->SC |= FTM_SC_PS(4);
    //左对齐，先高电平后低电平
    FTM_CnSC_REG(FTM_ARR[ftmNo], channel) |= FTM_CnSC_ELSB_MASK;
    //边沿对齐
    FTM_CnSC_REG(FTM_ARR[ftmNo], channel) &= ~FTM_CnSC_ELSA_MASK;
    FTM_CnSC_REG(FTM_ARR[ftmNo], channel) |= FTM_CnSC_MSB_MASK;
    //计数器清零
    FTM_ARR[ftmNo]->CNT=0;
    //中断禁止
    FTM_ARR[ftmNo]->SC &=  ~FTM_SC_TOIE_MASK;
    //FTM2使能
    FTM_ARR[ftmNo]->MODE &= ~FTM_MODE_FTMEN_MASK;
    //启用需要的输出通道，屏蔽其他通道
    FTM_ARR[ftmNo]->OUTMASK = (0xFE << channel);
    //禁止双边沿捕捉模式
    FTM_ARR[ftmNo]->COMBINE = 0;
    //FTM2计数初始值为0
    FTM_ARR[ftmNo]->CNTIN = 0;
    //周期=(MOD-CNTIN+1)*时钟周期=2.5ms
    FTM_ARR[ftmNo]->MOD = mod;
    MOD_VALUE = mod;
    //计算通道寄存器的值，设置占空比
    duty_channel = (uint_16)((float)mod * duty / 100);
    //设置通道值寄存器
    FTM_CnV_REG(FTM_ARR[ftmNo], channel) = duty_channel;
    //使用总线时钟
    FTM_ARR[ftmNo]->SC |= FTM_SC_CLKS(1);
}

//============================================================================
//函数名称：FTM_PWM_set_duty
//函数返回：无
//参数说明：ftmNo:FTM模块号：FTM_0、FTM_1、FTM_2
//          channel:选择通道号：FTM0和FTM1：通道0、通道1
//                             FTM2:通道0、1、2、3、4、5
//          duty：占空比：精度取决于设置的mod值，精度为1/mod。
//功能概要：初始化PWM模块
//============================================================================
void FTM_PWM_set_duty(uint_8 ftmNo, uint_8 channel, float duty)
{
	uint_16 duty_channel;

	if(duty > 100)
		duty = 100;
	if(duty < 0)
		duty = 0;
    //写保护禁止
    // FTM_ARR[ftmNo]->MODE |= FTM_MODE_WPDIS_MASK;
    //计算通道寄存器的值，设置占空比
    duty_channel = (uint_16)((float)MOD_VALUE * duty / 100);
    //设置通道值寄存器
    FTM_CnV_REG(FTM_ARR[ftmNo], channel) = duty_channel;
}


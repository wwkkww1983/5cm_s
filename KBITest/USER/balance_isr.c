//===========================================================================
//文件名称：balance_isr.h
//功能概要：中断函数文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-04-22 v1.0
//芯片类型：KEAZ128
//作者：YTom
//===========================================================================
#include "project.h"

//============================================================================
//函数名称：
//函数返回：
//参数说明：	FTM1_IRQHandler for encoder_2
//			FTM0_IRQHandler for encoder_1
//功能概要：
//============================================================================
//传动比~3
//计算：INCAP_CLOCK*60/avg/encoder1CirclePulse; // Speed in rpm
//      375000*60/512/avg/3
int_16 frequency[2] = {0,0};
int_16 countLoop[2] = {0,0};
float speedRPM[2] 	= {0,0};
int avg = 0;

uint16_t encoder_Count0 = 0;
uint16_t encoder_Count1 = 0;

void FTM0_IRQHandler(){
	if(isEncoderFlagSet(ENCODER_1)){
		encoder_Count0++;
		EncoderClrFlag(ENCODER_1);
	}
	
}
void FTM1_IRQHandler(){
	if(isEncoderFlagSet(ENCODER_2)){
		encoder_Count1++;
		EncoderClrFlag(ENCODER_2);
	}
}
//============================================================================
//函数名称：
//函数返回：
//参数说明：
//功能概要：
//============================================================================
void KBI0_IRQHandler(){
	/*handle KBI interruption*/
	static uint_8 i;
	static uint_32 flag, record = 0;
	
	if(isKBIFlagSet(KBI_0)) {
		KBI0_SC &= ~KBI_SC_KBIE_MASK;			// Disable IRQ
		
		//detect which of the keys have been pressed
		flag = KBI0_SP&KBIMASK;
		for(i=0;i<ANTISHAKETIME;i++){
			if(flag^(KBI0_SP&KBIMASK)) {
				break;
			}
			delay_us(200);
		}
		
		if(i>=ANTISHAKETIME){	// Confirm a movement
		/* Now press off and last is on, Detect low level(on)*/
			//keyboard1 pressed for the second time, dataIncrement()
			if(IS_OLED_MODE && (flag&kbi_Press1) && (record&kbi_Press1)){ 
				record^=kbi_Press1; kbi0_Low(kbi_Press1);
				dataIncrement();
			}//keyboard6 pressed for the second time, dataDecrement()				
			if(IS_OLED_MODE && (flag&kbi_Press6) && (record&kbi_Press6)){
				record^=kbi_Press6; kbi0_Low(kbi_Press6);
				dataDecrement();
			}//keyboard3 pressed for the second time, pageUp()	
			if(IS_OLED_MODE && (flag&kbi_Press3) && (record&kbi_Press3)){
				record^=kbi_Press3; kbi0_Low(kbi_Press3); 
				pageSwitch();
			}//keyboard4 pressed for the second time, lineUp()	
			if(IS_OLED_MODE && (flag&kbi_Press4) && (record&kbi_Press4)){ 
				record^=kbi_Press4; kbi0_Low(kbi_Press4);
				lineSwitch();
			}//keyboard2 pressed for the second time, go into BALANCEs mode
			if(!IS_BALANCE_MODE && (flag&kbi_Press2) && (record&kbi_Press2)){
				record^=kbi_Press2; kbi0_Low(kbi_Press2);
				
				
				setGoalRPM[0] = 0.0;
				setGoalRPM[1] = 0.0;
				
				PIDInit(&PID_Posi[0],PID_pos_p/10.0,PID_pos_i/10.0,PID_pos_d/100.0,maxLIM);
				PIDInit(&PID_Posi[1],PID_pos_p/10.0,PID_pos_i/10.0,PID_pos_d/100.0,maxLIM);
				
				PIDInit(&PID_Speed[0],PID_spd_p/1000.0,PID_spd_i/10.0,PID_spd_d/10.0,maxLIM);
				PIDInit(&PID_Speed[1],PID_spd_p/1000.0,PID_spd_i/10.0,PID_spd_d/10.0,maxLIM);
				
				globalResetMid();
				
				SET_CLEAR_OLED();
				CLR_OLED_MODE();
				CLR_DRIVING_MODE();
				SET_BALANCE_MODE();

				currentDuty[0] = 0;
				currentDuty[1] = 0;

				
			}//keyboard5 pressed for the second time, go into DRIVING mode
			if(!IS_DRIVING_MODE && (flag&kbi_Press5) && (record&kbi_Press5)){
				record^=kbi_Press5; kbi0_Low(kbi_Press5);
				
//				globalResetMid();
				SET_CLEAR_OLED();
				CLR_OLED_MODE();
				CLR_BALANCE_MODE();
				SET_DRIVING_MODE();

				currentDuty[0] = 0;
				currentDuty[1] = 0;

//				setGoalRPM[0] = 0.0;
//				setGoalRPM[1] = 0.0;
			}//Return to oled mode when pressing keyboard2 in balance mode
			if(IS_BALANCE_MODE && (flag&kbi_Press2) && (record&kbi_Press2)){
				record^=kbi_Press2; kbi0_Low(kbi_Press2);
				SET_OLED_MODE();
				CLR_DRIVING_MODE();
				CLR_BALANCE_MODE();
			}
//-------------------------------------------------------------------------
		/* Now press on, Detect high level(off)*/
			//keyboard1-6 pressed for the first time
			if(!(flag&kbi_Press1) && !(record&kbi_Press1))	{ record^=kbi_Press1; kbi0_High(kbi_Press1); }	
			if(!(flag&kbi_Press2) && !(record&kbi_Press2))	{ record^=kbi_Press2; kbi0_High(kbi_Press2); }	
			if(!(flag&kbi_Press3) && !(record&kbi_Press3))	{ record^=kbi_Press3; kbi0_High(kbi_Press3); }	
			if(!(flag&kbi_Press4) && !(record&kbi_Press4))	{ record^=kbi_Press4; kbi0_High(kbi_Press4); }	
			if(!(flag&kbi_Press5) && !(record&kbi_Press5))	{ record^=kbi_Press5; kbi0_High(kbi_Press5); }	
			if(!(flag&kbi_Press6) && !(record&kbi_Press6))	{ record^=kbi_Press6; kbi0_High(kbi_Press6); }	
		}
		
		KBIClear(KBI_0);
		KBI0_SC |= KBI_SC_KBIE_MASK;//Enable interrupt
	}
}
//============================================================================
//函数名称：
//函数返回：
//参数说明：
//功能概要：
//============================================================================
//ADCREAD_TIME				//read ADC every 200us
//GYRO_ACCE_TIME			//read gyro&acce every 400us
//POSITION_TIME				//compute position every 2ms
//ENCODER_TIME				//read encoder every 5ms
//SPEED_CONTRO_LTIME		//run speed control every 40ms
//DIR_CONTROL_TIME			//run direction control every 2ms
//BALANCE_CONTROL_TIME		//run balance control every 2ms
//OLED_CHANGE_TIME			//update oled display every 20ms
void PIT_CH0_IRQHandler(void){
	// To calculate how many times the programme has stepped into the interrupt
	// uint_32=4,294,967,296/2000(1s)/3600(1h)/24(1day)/365(1year)=25days
	// So we DON'T need to clear this value
	static uint_32 count = 0;		
	count ++;
	/*set peripheral flags*/
	if(count%ADCREAD_TIME == 0)			{	SET_ADCREAD_FLAG();		}
	if(count%GYRO_ACCE_TIME == 0)		{	SET_GYROACCE_FLAG();	}
	if(count%POSITION_TIME == 0)		{	SET_POSITION_FLAG();	}
	if(count%ENCODER_TIME == 0)			{	SET_ENCODER_FLAG();		}
	if(count%SPEED_CONTRO_LTIME == 0)	{	SET_SPEED_CONTROL();	}
	if(count%DIR_CONTROL_TIME == 0)		{	SET_DIRECTION_CONTROL();}
	if(count%BALANCE_CONTROL_TIME == 0)	{	SET_BALANCE_CONTROL();	}
	if(count%OLED_CHANGE_TIME == 0)		{	SET_DISP_REFRESH();		}
	if(count%2000==0) 					{	globalCount++;			}
	
	pit_IRQClearFlag(pit_CH0);
}


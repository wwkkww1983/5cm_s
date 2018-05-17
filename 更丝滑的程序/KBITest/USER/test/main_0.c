#include "KBI.h"
#include "balanceControl.h"
#include "OLED.h"
#include "GYRO.h"
#include "pit.h"
#include "delay.h"
#include "display.h"
#include "string.h"
#include "accelerometer.h"
#include "includes.h"
#include "math.h"

uint_8 peripheralRun;

/*KBI DIFINITIONS*/
/* KBI0 */
#define	kbi_PTA(x)			(((uint_32)1<<(x))<<0)
#define	kbi_PTB(x)			(((uint_32)1<<(x))<<8)
#define	kbi_PTC(x)			(((uint_32)1<<(x))<<16)
#define	kbi_PTD(x)			(((uint_32)1<<(x))<<24)
/* KBI1 */
#define	kbi_PTE(x)			(((uint_32)1<<(x))<<0)
#define	kbi_PTF(x)			(((uint_32)1<<(x))<<8)
#define	kbi_PTG(x)			(((uint_32)1<<(x))<<16)
#define	kbi_PTH(x)			(((uint_32)1<<(x))<<24)
/*KBI On-board presses */
#define kbi_Press1			kbi_PTC(7)
#define kbi_Press2			kbi_PTA(3)
#define kbi_Press3			kbi_PTD(3)
#define kbi_Press4			kbi_PTC(6)	
#define kbi_Press5			kbi_PTA(2)
#define kbi_Press6			kbi_PTD(4)
#define kbi0_Low(port)		KBI0_ES &= ~(port)
#define kbi0_High(port)		KBI0_ES |= (port)

#define KBIMASK 			(kbi_Press1|kbi_Press2|kbi_Press3|kbi_Press4|kbi_Press5|kbi_Press6)
#define ANTISHAKETIME 		30

/*RUNNING MODE DEFINITIONS: 'OLED MODE','BALANCE MODE','DRIVING MODE'*/
#define IS_OLED_MODE 			(runningMode&(0x01))
#define IS_BALANCE_MODE			(runningMode&(0x02))
#define IS_DRIVING_MODE			(runningMode&(0x04))
#define SET_OLED_MODE()			(runningMode|=(0x01))
#define SET_BALANCE_MODE()		(runningMode|=(0x02))
#define SET_DRIVING_MODE()		(runningMode|=(0x04))
#define CLR_OLED_MODE()			(runningMode&=~(0x01))
#define CLR_BALANCE_MODE()		(runningMode&=~(0x02))
#define CLR_DRIVING_MODE()		(runningMode&=~(0x04))

/*typedef struct{
	int_8  argName[6];	//argument name
	int_16* argValue;	//argument value
	uint_8  delta;		//argument variation
}displayItem, *pdisplayItem;*/

uint_8 runningMode;
uint_8 val[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
int_16 getXYZ[3] = {0};
int_16 gyroValue[5], xAxis[5], zAxis[5], angVelocity, xAxisMean, zAxisMean, gyroMean;
int_16 acceAngle, gyroAngle, KalmanAngle;

float a= -2.5;
int_16 b;
int main(){
    //int_8 text[] = "KBI TEST";	
	  int_16 array[3] = {20,50,80};
		uint_8 index;

		pitInit_us(pit_CH0, 500);
		acceInit(MMA_12bit_Mode, MMA_Sensi_2g);
		GYROInit();
		int_16 gyroMid;
    OLED_Init();
	  OLED_Clear();
	  //OLED_ShowString(0,0,text);
		b = (int_16)a;
		//OLED_ShowChar(56,2,'*');
		//dis_num(0,2,b);
	
    KBIInit(KBI_0|23,FALLING,1);    //Press 1
    KBIInit(KBI_0|3,FALLING,1);     //Press 2
    KBIInit(KBI_0|27,FALLING,1);    //Press 3
    KBIInit(KBI_0|22,FALLING,1);    //Press 4
    KBIInit(KBI_0|2,FALLING,1);     //Press 5
    KBIInit(KBI_0|28,FALLING,1);    //Press 6
		
		//gyroscope initialize
		acceReadL(MMA_ADDR, 0x01, 6, val);
		acceSolveData(MMA_12bit_Mode, val, getXYZ);
		gyroAngle = atan2(-getXYZ[0],-getXYZ[2])*180/PI;
	
	  displayItem items[DATANUM];
		strcpy(items[0].argName,"xAxi1");
		items[0].argValue = &array[0];
		items[0].delta = 2;

		strcpy(items[1].argName,"yAxi2");
		items[1].argValue = &array[1];
		items[1].delta = 3;

		strcpy(items[2].argName,"zAxi3");
		items[2].argValue = &array[2];
		items[2].delta = 5;
		
		strcpy(items[3].argName,"xAxis");
		items[3].argValue = &getXYZ[0];
		items[3].delta = 0;

		strcpy(items[4].argName,"yAxis");
		items[4].argValue = &getXYZ[1];
		items[4].delta = 0;

		strcpy(items[5].argName,"zAxis");
		items[5].argValue = &getXYZ[2];
		items[5].delta = 0;
		
		strcpy(items[6].argName,"GYRO ");
		items[6].argValue = &angVelocity;
		items[6].delta = 0;
		
		strcpy(items[7].argName,"GYMid");
		items[7].argValue = &gyroMid;
		items[7].delta = 0;
		
		strcpy(items[8].argName,"acAng");
		items[8].argValue = &acceAngle;
		items[8].delta = 0;
		
		strcpy(items[9].argName,"klAng");
		items[9].argValue = &KalmanAngle;
		items[9].delta = 0;
	
	  /*uint_8 index;
		OLED_Clear();

		for(index=0; (index<MAXLINE) && (index+MAXLINE*page)<DATANUM; index++){
			OLED_ShowString(0,2*index, items[index+MAXLINE*page].argName);
			OLED_ShowNum(72,2*index, *(items[index+MAXLINE*page].argValue),6,16);
		}
		OLED_ShowChar(64,2*line,'*');*/
		
		gyroMid = getGyroMid(VO1);
	  while(1){
			if(IS_DISP_CHANGED){
					CLR_DISP_CHANGE();
					OLEDDisplay(items);
			}
			if(GYRO_ACCE_FLAG){
					static uint_8 count;
					if(count++ == 4) count = 0;
				
					CLR_GYROACCE_FLAG();
					acceReadL(MMA_ADDR, 0x01, 6, val);
					acceSolveData(MMA_12bit_Mode, val, getXYZ);
				
					gyroValue[count] = -GYROReadn(VO1,5)+gyroMid;			
					xAxis[count] = getXYZ[0];
					zAxis[count] = getXYZ[2];
					
					if(count == BALANCECOUNT){
						for(index = 0; index <= BALANCECOUNT; index++){
							xAxisMean += xAxis[index];
						}
						xAxisMean = xAxisMean / (BALANCECOUNT+1);	
						
						for(index = 0; index <= BALANCECOUNT; index++){
							zAxisMean += zAxis[index];
						}
						zAxisMean = zAxisMean / (BALANCECOUNT+1);
						
						for(index = 0; index <= BALANCECOUNT; index++){
							gyroMean += gyroValue[index];
						}
						gyroMean = gyroMean / (BALANCECOUNT+1);
						
						acceAngle = atan2(-xAxisMean,-zAxisMean )*180/PI;
						angVelocity = gyroMean * 0.2;
						KalmanAngle = KALMANFilter(angVelocity,acceAngle);
					}
			}
			if(BALANCE_CONTROL){
					CLR_BALANCE_CONTROL();
			}
		}
}

void PIT_CH0_IRQHandler(void){
	//To calculate how many times the programme has stepped into the interrupt
	static uint_16 count;

	/*set peripheral flags*/
	if(count%GYRO_ACCE_TIME == 0)				SET_GYROACCE_FLAG();
	if(count%OLED_CHANGE_TIME == 0)			SET_DISP_CHANGE();
	if(count%BALANCE_CONTROL_TIME == 0)	SET_BALANCE_CONTROL();
	

	if(count++ == ELAPSE_TIME){
			count = 0;
	}
	pit_IRQClearFlag(pit_CH0);
}


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
			if((flag&kbi_Press1) && (record&kbi_Press1)){ 
				record^=kbi_Press1; kbi0_Low(kbi_Press1);
				dataIncrement();
			}//keyboard6 pressed for the second time, dataDecrement()				
			if((flag&kbi_Press6) && (record&kbi_Press6)){
				record^=kbi_Press6; kbi0_Low(kbi_Press6);
				dataDecrement();
			}//keyboard2 pressed for the second time, lineUp()
			if((flag&kbi_Press2) && (record&kbi_Press2)){
				record^=kbi_Press2; kbi0_Low(kbi_Press2);
				lineUp();
			}//keyboard5 pressed for the second time, lineDown()	
			if((flag&kbi_Press5) && (record&kbi_Press5)){
				record^=kbi_Press5; kbi0_Low(kbi_Press5); 
				lineDown();
			}//keyboard3 pressed for the second time, pageUp()	
			if((flag&kbi_Press3) && (record&kbi_Press3)){
				record^=kbi_Press3; kbi0_Low(kbi_Press3); 
				pageUp();
			}//keyboard4 pressed for the second time, pageDown()	
			if((flag&kbi_Press4) && (record&kbi_Press4)){ 
				record^=kbi_Press4; kbi0_Low(kbi_Press4);
				pageDown();
			}//keyboard3&keyboard4 are pressed at the same time
			if((flag&kbi_Press3) && (record&kbi_Press3) && (flag&kbi_Press4) && (record&kbi_Press4)){
				if(IS_OLED_MODE){
					CLR_OLED_MODE();
					SET_BALANCE_MODE();
				}else if(IS_BALANCE_MODE){
					CLR_BALANCE_MODE();
					SET_OLED_MODE();
				}else{
					CLR_BALANCE_MODE();
					CLR_DRIVING_MODE();
					SET_OLED_MODE();
				}
			}//keyboard2&keyboard5 are pressed at the same time, enable&disable Driving mode
			if((flag&kbi_Press2) && (record&kbi_Press2) && (flag&kbi_Press5) && (record&kbi_Press5)){	
				if(IS_DRIVING_MODE){
					CLR_DRIVING_MODE();
					SET_OLED_MODE();
				}else{
					CLR_OLED_MODE();
					CLR_BALANCE_MODE();
					SET_DRIVING_MODE();
				}
			}
		/* Now press on, Detect high level(off)*/
			//keyboard1-6 pressed for the first time
			if(!(flag&kbi_Press1) && !(record&kbi_Press1))	
					{ record^=kbi_Press1; kbi0_High(kbi_Press1); }	
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

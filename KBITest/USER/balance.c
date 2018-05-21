//===========================================================================
//FIleName:	balance.c
//Function:
//版权所有:	TU-Smart from Tongji Univ.
//版本更新:	2018-04-18 v1.0
//芯片类型:	KEAZ128
//作者：	YTom
/*
Pin mapping:
(ok)PWM			PWM1,2		1 H0, 2 H1
				PWM3,4		3 G4, 4 G5
(ok)SpeedFBK	Encode1		A1			Direction1	A0(as GPIO_IN not FTM_IN)
				Encode2		C5			Direction2	C4(as GPIO_IN not FTM_IN)
(ok)Gyro		I2C_SDA	B6
				I2C_SCL	B7
(ok)Acce(ADC):	VO1	A6		VO2	F5		VO3	A7
	KBI:		K1	C7	Data+
				K2	A3	balance mode
				K3	D3	Page+
				K4	C6	Line+
				K5	A2	driving mode
				K6	D4	Data-
	ADC:		CH1			CH2			CH3
				CH4			CH5			CH6
				CH7

ATTENTION:
	Global PIT time unit = 0.5ms
	Encoder work with FTM in 375kHz frequency,
		FTM1=Left,	FTM2=Right
	K1,K6 for +/-
	K3,K4 for Page U/D
	K2,K5 for Line U/D

*/
//===========================================================================
#include "project.h"

// (encoder_Count0/512)/(0.004s)*60*();
#define SPEED_INDEX		8.1380f

// Global variable for WHOLE porject
uint_8 peripheralRun = 0;
uint_8 runningMode = 0;

// Global variable
uint_8 rawAcce[8] 		= {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
int_16 acceValue[3] 	= {0};
int_16 gyroValue[5], xAxis[5], zAxis[5], angVelocity, xAxisMean, zAxisMean, gyroMean;
float Fil[10]={0.7,0.05,0.04,0.04,0.04,0.04,0.03,0.03,0.02,0.01};
int_16 Data_Res[10][10],Data_New[10]={0,0,0,0,0,0,0,0,0,0};
int_16 acceAngle, gyroAngle;
float KalmanAngle;
float TargetAngle;
int_16 sSpeed[2] 		= {0,0};			
float	 currentDuty[2] = {0.f,0.f}, speedTarget = 500;
float  speedDuty 	= 0;
float  speedDutyPrev = 0;
float  balanceDuty 	= 0;
float dirDutyDif = 0;//yan
int_16 targetX=2500, currentX;//yan
float  setGoalRPM[2] 	= {0.f,0.f};		// Speed Goal
float meanSpeed = 0;
int_16 globalCount 		= 0;

// Local variable
//int_16 		array[3] = {};
displayItem items[DATANUM];
float 		GyroMid;
PID 		PID_Speed[2];
PID 		PID_Posi[2];
PID			PID_Dir;//yan
int_16		delta;
int_16		GM,KA;

int_16 PID_pos_p 	= 11;		// /10
int_16 PID_pos_i	= 0;		// /10
int_16 PID_pos_d	= 480;		// /100

int_16 PID_spd_p 	= 5;		// /1000
int_16 PID_spd_i	= 0;		// /10
int_16 PID_spd_d	= 0;		// /10

int_16 speedIndex = 5;		// /200
int_16 deltaExp = 10;		// *1.0
int_16 maxLIM = 40;			//
int_16 spdLimit = 50.0;

int_16 ADCVal_01 = 0, ADCVal_03 = 0;

void globalDisplayInit(void);
void globalKBIInit(void);
void globalKalmanLoop(void);
float PIDLimit(float value, float limit);

int main(){
	// Accelerometer initialize
	acceInit(MMA_12bit_Mode, MMA_Sensi_2g);
	// Gyroscope initialize
	GYROInit();
	// OLED and display initialize
	OLED_Init();
	OLED_Clear();
	globalDisplayInit();
	SET_DISP_REFRESH();		// Set diaplay refresh flag
	// KBI initialize
	globalKBIInit();
	// Encoders initialization
	initEncoder(ENCODER_2);
	initEncoder(ENCODER_1);
	// Motors initialization
	initMotor(MOTOR_1,10);	// Output frequency 10kHz
	initMotor(MOTOR_2,10);
	// PID initialization
	
	CLR_SPEED_CONTROL();

	// Firstly read value
//	acceReadL(MMA_ADDR, 0x01, 6, rawAcce);
//	acceSolveData(MMA_12bit_Mode, rawAcce, acceValue);
//	gyroAngle = atan2(-acceValue[0],-acceValue[2])*180/PI;
	GyroMid = getGyroMid(VO3);

//	GyroMid = 0;
	
	// For test
//	setGoalRPM[0] = 400.0;
//	setGoalRPM[1] = 400.0;
//	SET_CLEAR();
//	CLR_OLED_MODE();
//	CLR_DRIVING_MODE();
//	SET_BALANCE_MODE();

	SET_OLED_MODE();
	CLR_BALANCE_MODE();
	CLR_DRIVING_MODE();
	
//	setForwDuty(MOTOR_1,30);
//	setForwDuty(MOTOR_2,30);
	
	// PIT initialize, TimeUnit=0.5ms, global timer
	// This means start ALL works
	pitInit_us(pit_CH0, GLOBAL_TIME_UNIT);
	
	while(1){
		if(DISP_REFRESH){
			CLR_DISP_REFRESH();
			if(IS_OLED_MODE){
				// Refresh display
				GM = GyroMid;
				KA = KalmanAngle;
				OLEDDisplay(items);
				setForwDuty(MOTOR_1,0);
				setForwDuty(MOTOR_2,0);
			}else if(IS_BALANCE_MODE){
				if(IS_CLEAR_OLED) {
					CLR_CLEAR_OLED();
					OLED_Clear();
					OLED_ShowString(0,2,"Balance...");
				}
					OLED_ShowString(0,2,"Balance...");
					
					//OLED_ShowString(0,3,"anTar");
					dis_num(0,3,TargetAngle);
					//OLED_ShowString(0,4,"acceA");
					dis_num(0,4,acceAngle);
					//OLED_ShowString(0,5,"kalAn");
					dis_num(0,5,KalmanAngle);
				
			}else if(IS_DRIVING_MODE) {
				if(IS_CLEAR_OLED) {
					CLR_CLEAR_OLED();
					OLED_Clear();
					OLED_ShowString(0,0,"Driving...");
				}
				OLED_ShowString(0,2,"Driving...");
					
				//OLED_ShowString(0,3,"anTar");
				dis_num(0,3,TargetAngle);
				//OLED_ShowString(0,4,"acceA");
				dis_num(0,4,acceAngle);
				//OLED_ShowString(0,5,"kalAn");
				dis_num(0,5,KalmanAngle);
				OLED_ShowString(0,6,"curDu");
				dis_num(0,6,currentDuty[1]);
				dis_num(0,7,meanSpeed);
			}
		}
		if(ADC_READ_FLAG){
			CLR_ADCREAD_FLAG();
//			ADCVal_01 = ADCReadn(ADC_1,5);
//			ADCVal_03 = ADCReadn(ADC_3,5);
			ADC_Read(Data_Res);
			ADC_Smoothing(Data_Res,Data_New,Fil);
			currentX = getX(Data_New);
		}
		if(GYRO_ACCE_FLAG){
			CLR_GYROACCE_FLAG();
			// Refresh GYRO and ACCE
			globalKalmanLoop();
		}
		if(ENCODER_FLAG){
			CLR_ENCODER_FLAG();
			speedRPM[0]=encoder_Count0*SPEED_INDEX;
			speedRPM[1]=encoder_Count1*SPEED_INDEX;
			// Read value
			frequency[0] = speedRPM[0];
			frequency[1] = speedRPM[1];
			// Reset value for next read
			encoder_Count0 = 0;
			encoder_Count1 = 0;
		}
		if((IS_BALANCE_MODE) && (BALANCE_CONTROL)){
			CLR_BALANCE_CONTROL();
			// PID controls
//			delta = GyroMid-KalmanAngle;
//			setGoalRPM[0] = setGoalRPM[1] = fabs(delta*deltaExp*1.0);
//			sendSpeed[0] = calcDuty(PIDcalc(&PID_Speed[0],setGoalRPM[0],speedRPM[0]));
//			sendSpeed[1] = calcDuty(PIDcalc(&PID_Speed[1],setGoalRPM[1],speedRPM[1]));
			
			balanceDuty = PIDcalc(&PID_Posi[0],TargetAngle,KalmanAngle);
			currentDuty[1] += balanceDuty;
			
			currentDuty[1] = (currentDuty[1]>30.)?30.0:((currentDuty[1]<-30.)?-30.0:currentDuty[1]);
			
//			if(sendSpeed[1]>0){
//				setForwDuty(MOTOR_1,PIDLimit(calcDuty(sendSpeed[1]),spdLimit));
//				setForwDuty(MOTOR_2,PIDLimit(calcDuty(sendSpeed[1]),spdLimit)+1.0);
//			}else{
//				setReveDuty(MOTOR_1,PIDLimit(calcDuty(-sendSpeed[1]),spdLimit)+3.0);
//				setReveDuty(MOTOR_2,PIDLimit(calcDuty(-sendSpeed[1]),spdLimit)+3.0+1.0);
//			}
			
			if(currentDuty[1]>0){
				//sendSpeed[1] = PIDcalc(&PID_Speed[1],sendSpeed[1],speedRPM[1]);
				//setForwDuty(MOTOR_1,PIDLimit(calcDuty(sendSpeed[1]),spdLimit));
				//setForwDuty(MOTOR_2,PIDLimit(calcDuty(sendSpeed[1]),spdLimit)+1.0);
				setForwDuty(MOTOR_1,currentDuty[1]);
				setForwDuty(MOTOR_2,currentDuty[1]);
			}else{
				//sendSpeed[1] = PIDcalc(&PID_Speed[1],-sendSpeed[1],speedRPM[1]);
				//setReveDuty(MOTOR_1,PIDLimit(calcDuty(sendSpeed[1]),spdLimit)+3.0);
				//setReveDuty(MOTOR_2,PIDLimit(calcDuty(sendSpeed[1]),spdLimit)+3.0+1.0);
				setReveDuty(MOTOR_1,-currentDuty[1]);
				setReveDuty(MOTOR_2,-currentDuty[1]);
			}
		}
		if(IS_DRIVING_MODE){
			if(SPEED_CONTROL){
				CLR_SPEED_CONTROL();
				meanSpeed = (speedRPM[0] + speedRPM[1])/2;
				speedDutyPrev = speedDuty;
				speedDuty = -PIDcalc(&PID_Speed[0],speedTarget,meanSpeed);
				//speedDuty = -10;
			}
			//if(DIRECTION_CONTROL){
			//		CLR_DIRECTION_CONTROL();
			//		dirDutyDif = PIDcalc(&PID_Dir, targetX, currentX);
			//}
			if(BALANCE_CONTROL){
				CLR_BALANCE_CONTROL();
				balanceDuty = PIDcalc(&PID_Posi[0],TargetAngle,KalmanAngle);
				
				// overall motor currentDutycontrol, with control time same as BALANCE_CONTROL
				currentDuty[0] = currentDuty[0]+speedDuty+balanceDuty+dirDutyDif;
				currentDuty[1] = currentDuty[1]+speedDuty+balanceDuty-dirDutyDif;

				//limit the duty set to moto
				currentDuty[0] = (currentDuty[0]>50.)?50.0:((currentDuty[0]<-50.)?-50.0:currentDuty[0]);
				currentDuty[1] = (currentDuty[1]>50.)?50.0:((currentDuty[1]<-50.)?-50.0:currentDuty[1]);

				if(currentDuty[0]>0) {
					setForwDuty(MOTOR_1,currentDuty[0]);
				}else{
					setReveDuty(MOTOR_1,-currentDuty[0]);
				}
			
				if(currentDuty[1]>0) {
					setForwDuty(MOTOR_2,currentDuty[1]);
				}else{
					setReveDuty(MOTOR_2,-currentDuty[1]);
				}
			}
		}	
	}
}

float PIDLimit(float value, float limit)
{
	return (value>limit)?limit:value;
}

//============================================================================
//============================================================================
void globalResetMid(void)
{
	TargetAngle = KalmanAngle;
}

//============================================================================
//============================================================================
void globalKalmanLoop(void)
{
	static uint_8 index;
	static uint_8 count;
	if(count++ == 4) count = 0;
	acceReadL(MMA_ADDR, 0x01, 6, rawAcce);
	acceSolveData(MMA_12bit_Mode, rawAcce, acceValue);

	gyroValue[count] = -GYROReadn(VO3,5)+GyroMid;			
	xAxis[count] = acceValue[0];
	zAxis[count] = acceValue[2];
	
	if(count == BALANCECOUNT){
		xAxisMean = 0;
		zAxisMean = 0;
		gyroMean  = 0;
		
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
		if(acceAngle>0) acceAngle -= 360.0;
		angVelocity = gyroMean * 0.2;
		KalmanAngle = KALMANFilter(angVelocity,acceAngle);
		if(KalmanAngle>0) KalmanAngle -= 360.0;					////
	}
}
//============================================================================
//============================================================================
void globalDisplayInit(void)
{
	strcpy(items[0].argName,"VecA0");	// Velocity from encoder_1
	items[0].argValue = &frequency[0];
	items[0].sensorVal = 1;
	items[0].pageNum = SENSOR_PAGE;
	
	strcpy(items[1].argName,"VecA1");	// Velocity from encoder_2
	items[1].argValue = &frequency[1];
	items[1].sensorVal = 1;
	items[1].pageNum = SENSOR_PAGE;
	
	strcpy(items[2].argName,"Cunt1");	// Tire round from encoder_1
	items[2].argValue = &countLoop[0];
	items[2].pageNum = DATA0_PAGE;
	
	strcpy(items[3].argName,"Cunt2");	// Tire round from encoder_1
	items[3].argValue = &countLoop[1];
	items[3].pageNum = DATA0_PAGE;
	
	strcpy(items[4].argName,"VecS1");	// Velocity sent to motor 1
	items[4].argValue = &sSpeed[0];
	items[4].pageNum = DATA0_PAGE;
	
	strcpy(items[5].argName,"VecS2");	// Velocity sent to motor 2
	items[5].argValue = &sSpeed[1];
	items[5].pageNum = DATA0_PAGE;
	//============================================================================
	strcpy(items[6].argName,"xAxis");	//
	items[6].argValue = &acceValue[0];
	items[6].pageNum = SENSOR_PAGE;

	strcpy(items[7].argName,"yAxis");	//
	items[7].argValue = &acceValue[1];
	items[7].pageNum = SENSOR_PAGE;

	strcpy(items[8].argName,"zAxis");	//
	items[8].argValue = &acceValue[2];
	items[8].pageNum = SENSOR_PAGE;

	strcpy(items[9].argName,"GYROv");	//
	items[9].argValue = &angVelocity;
	items[9].pageNum = DATA0_PAGE;

	strcpy(items[10].argName,"GYMid");	// Middle value of GYRO
	items[10].argValue = &GM;
	items[10].pageNum = DATA0_PAGE;

	strcpy(items[11].argName,"acAng");	// Angle from accelerometer
	items[11].argValue = &acceAngle;
	items[11].pageNum = DATA0_PAGE;

	strcpy(items[12].argName,"klAng");	// Angle from Kalman Filter
	items[12].argValue = &KA;
	items[12].pageNum = DATA0_PAGE;
	//============================================================================
	strcpy(items[13].argName,"gCUNT");	//
	items[13].argValue = &globalCount;
	items[13].pageNum = DATA1_PAGE;
	
	// strcpy(items[14].argName,"K_spd");	//
	// items[14].argValue = &speedIndex;
	// items[14].delta = 1;
	// items[14].changeable = 1;
	// items[14].pageNum = VARIABLE_PAGE;
	
	strcpy(items[14].argName,"pPIDp");	//
	items[14].argValue = &PID_pos_p;
	items[14].delta = 1;
	items[14].changeable = 1;
	items[14].pageNum = VARIABLE_PAGE;

	strcpy(items[15].argName,"pPIDi");	//
	items[15].argValue = &PID_pos_i;
	items[15].delta = 1;
	items[15].changeable = 1;
	items[15].pageNum = VARIABLE_PAGE;

	strcpy(items[16].argName,"pPIDd");	//
	items[16].argValue = &PID_pos_d;
	items[16].delta = 4;
	items[16].changeable = 1;
	items[16].pageNum = VARIABLE_PAGE;

	strcpy(items[17].argName,"sPIDp");	//
	items[17].argValue = &PID_spd_p;
	items[17].delta = 1;
	items[17].changeable = 1;
	items[17].pageNum = VARIABLE_PAGE;

	strcpy(items[18].argName,"sPIDi");	//
	items[18].argValue = &PID_spd_i;
	items[18].delta = 2;
	items[18].changeable = 1;
	items[18].pageNum = VARIABLE_PAGE;

	strcpy(items[19].argName,"sPIDd");	//
	items[19].argValue = &PID_spd_d;
	items[19].delta = 2;
	items[19].changeable = 1;
	items[19].pageNum = VARIABLE_PAGE;

	strcpy(items[20].argName,"K_spd");	//
	items[20].argValue = &speedIndex;
	items[20].delta = 1;
	items[20].changeable = 1;
	items[20].pageNum = VARIABLE_PAGE;
	
	strcpy(items[21].argName,"spdLM");	//
	items[21].argValue = &spdLimit;
	items[21].delta = 1;
	items[21].changeable = 1;
	items[21].pageNum = VARIABLE_PAGE;

	
	strcpy(items[22].argName,"ADC01");	//
	items[22].argValue = &ADCVal_01;
	items[22].pageNum = DATA1_PAGE;
	
	strcpy(items[23].argName,"ADC03");	//
	items[23].argValue = &ADCVal_03;
	items[23].pageNum = DATA1_PAGE;
	
	strcpy(items[24].argName,"ADC01");	
	items[24].argValue = &Data_New[0];
	items[24].sensorVal = 0;
	items[24].pageNum = DATA2_PAGE;

	strcpy(items[25].argName,"ADC02");	
	items[25].argValue = &Data_New[1];
	items[25].sensorVal = 0;
	items[25].pageNum = DATA2_PAGE;

	strcpy(items[26].argName,"ADC03");	
	items[26].argValue = &Data_New[2];
	items[26].sensorVal = 0;
	items[26].pageNum = DATA2_PAGE;

	strcpy(items[27].argName,"ADC04");	
	items[27].argValue = &Data_New[3];
	items[27].sensorVal = 0;
	items[27].pageNum = DATA2_PAGE;

	strcpy(items[28].argName,"ADC05");	
	items[28].argValue = &Data_New[4];
	items[28].sensorVal = 0;
	items[28].pageNum = DATA2_PAGE;

	strcpy(items[29].argName,"currX");	
	items[29].argValue = &currentX;
	items[29].sensorVal = 0;
	items[29].pageNum = DATA2_PAGE;
}
//============================================================================
//============================================================================
void globalKBIInit(void)
{
	KBIInit(KBI_0|23,FALLING,1);    //Press 1
    KBIInit(KBI_0|3,FALLING,1);     //Press 2
    KBIInit(KBI_0|27,FALLING,1);    //Press 3
    KBIInit(KBI_0|22,FALLING,1);    //Press 4
    KBIInit(KBI_0|2,FALLING,1);     //Press 5
    KBIInit(KBI_0|28,FALLING,1);    //Press 6
}




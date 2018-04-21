//===========================================================================
//文件名称：balanceControl.c
//功能概要：主方向控制环程序源文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-03-18  V1.0
//芯片类型：KEAZ128
//作者：Shine Wong
//===========================================================================
/*#include "accelerometer.h"
#include "GYRO.h"
#include "balanceControl.h"
#include "motor.h"
#include "PID.h"*/
#include "includes.h"
#include "balanceControl.h"
#include "common.h"


//===========================================================================
//Function: reads datas from the gyro&acce and computes the kalman angle and 
//			controls the motor
//Return: null(error handler)
//Arguements: null
//Others: this function is the main control programme of the autocar's balance
//		  and should be excuted every 2ms
//===========================================================================
//void balanceControl(pPID balancePID){
//	/*O.statements of the arguments*/
//	//stores the values read from the accelerometer directly
//	uint_8 acceValue[6],index;
//	//stores the values solved from acceValue&gyroscope
//	uint_16 xyzGravity[3],GYRORead, realAngle, angleError;
//	//the controlled quantity of autocar's balance, which in fact is a duty of the motors
//	uint_16 balanceControl;
//	/*the angle which the accelerometer solves & the angular velocity solved from the gyroscope
//	  both save the last five values*/
//	static float acceAngle[5],angleVelocity[5];
//	float meanAngle = 0, meanVelocity = 0;
//	/*count how many times the programme has entered the function(0~4) to determine
//	  whether a balance control should be excuted(every 10ms)*/
//	static uint_8 count = 0;
//	if(count++ == BALANCECOUNT) count = 0;

//	/*I.read datas*/
//	acceReadL(MMA_ADDR, 0x01, 6, acceValue);
//	acceSolveData(0, acceValue, xyzGravity);
//	GYRORead = GYROReadn(VO1,8);

//	/*II.solve data: gyro: digital --> w    acce: i2c --> gravity*/
//	acceAngle[count] = atan2(xyzGravity[0], xyzGravity[2]);
//	angleVelocity[count] = GYROSolve(GYRORead);

//	/*III.Kalman filter*/
//	//excute balance control every 10ms
//	if(count == BALANCECOUNT){
//		/*compute the mean angular velocity and the mean angle in the 10ms*/
//		for(index = 0; index <= BALANCECOUNT; index++){
//			meanAngle += acceAngle[index];
//		}
//		meanAngle = meanAngle / (BALANCECOUNT+1);

//		for(index = 0; index <= BALANCECOUNT; index++){
//			meanVelocity += angleVelocity[index];
//		}
//		meanVelocity = meanVelocity / (BALANCECOUNT+1);

//		//KALMAN Filter
//		realAngle = (uint_16)KALMANFilter(meanVelocity, meanAngle);

//		//PID Controller
//		angleError = balancePID -> target - realAngle;
//		balanceControl = PIDController(balancePID,angleError);

//	/*IV.control the motor*/
//		setDuty(MOTOR_1,balanceControl);
//		setDuty(MOTOR_2,balanceControl);
//	} 
//}

//===========================================================================
//Function: To deal with the datas read by the gyro&acce using kalman filter
//Return: returns the optimum angle obtained from the kalman filter
//Arguements: angVelocity: the angular velocity solved from the gyroscope
//			  acceAngle:   the angle solved from the accelerometer
//Others: the covariance Q&R is defined at the beginning of balanceControl.h
//===========================================================================

float KALMANFilter(float angVelocity, float acceAngle){
	//use the angle read from the accelerometer as the first optimum angle
	static float optimumAngle = 0;
	//define the initial covariance of the optimum angle
	static uint_16 optimumCovariance = INITIAL_COVARIANCE;
	//statement of the variables used in kalman kilter
	float estimateAngle, estimateCovariance, kalmanGain;

	/*kalman equations*/
	//X(k|k-1)=A X(k-1|k-1)+B U(k)				----1
	estimateAngle = optimumAngle + angVelocity*CONTROLTIME;
	//P(k|k-1)=A P(k-1|k-1) A’+Q  				----2
	estimateCovariance = optimumCovariance + Q;
	//Kg(k)= P(k|k-1) H’ / (H P(k|k-1) H’ + R)	----3 
	kalmanGain = estimateCovariance / (estimateCovariance+R);
	//X(k|k)= X(k|k-1)+Kg(k) (Z(k)-H X(k|k-1))	----4
	optimumAngle = estimateAngle + kalmanGain*(acceAngle - estimateAngle);
	//P(k|k)=（I-Kg(k) H）P(k|k-1)				----5
	optimumCovariance = (1-kalmanGain)*estimateCovariance;

	return optimumAngle;
}

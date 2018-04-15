#ifndef INCLUDES_H_
#define INCLUDES_H_

/*flags of some peripherals to detect whether they are to be operated*/
#define ADC_READ_FLAG			(peripheralRun&(0x01))
#define GYRO_ACCE_FLAG			(peripheralRun&(0x02))
#define POSITION_FLAG			(peripheralRun&(0x04))
#define ENCODER_FLAG			(peripheralRun&(0x08))
#define SPEED_CONTROL			(peripheralRun&(0x10))
#define DIRECTION_CONTROL		(peripheralRun&(0x20))
#define BALANCE_CONTROL 		(peripheralRun&(0x40))
#define IS_DISP_CHANGED			(peripheralRun&(0x80))

#define SET_ADCREAD_FLAG()		(peripheralRun|=(0x01))
#define SET_GYROACCE_FLAG()		(peripheralRun|=(0x02))
#define SET_POSITION_FLAG()		(peripheralRun|=(0x04))
#define SET_ENCODER_FLAG()		(peripheralRun|=(0x08))
#define SET_SPEED_CONTROL()		(peripheralRun|=(0x10))
#define SET_DIRECTION_CONTROL()	(peripheralRun|=(0x20))
#define SET_BALANCE_CONTROL()	(peripheralRun|=(0x40))
#define SET_DISP_CHANGE()		(peripheralRun|=(0x80))

#define CLR_ADCREAD_FLAG()		(peripheralRun&=~(0x01))
#define CLR_GYROACCE_FLAG()		(peripheralRun&=~(0x02))
#define CLR_POSITION_FLAG()		(peripheralRun&=~(0x04))
#define CLR_ENCODER_FLAG()		(peripheralRun&=~(0x08))
#define CLR_SPEED_CONTROL()		(peripheralRun&=~(0x10))
#define CLR_DIRECTION_CONTROL()	(peripheralRun&=~(0x20))
#define CLR_BALANCE_CONTROL()	(peripheralRun&=~(0x40))
#define CLR_DISP_CHANGE()		(peripheralRun&=~(0x80))

#define ADCREAD_TIME			1u 			//read ADC every 200us
#define GYRO_ACCE_TIME			2u 			//read gyro&acce every 400us
#define POSITION_TIME			10u 		//compute position every 2ms
#define ENCODER_TIME			25u			//read encoder every 5ms
#define SPEED_CONTRO_LTIME		25u			//run speed control every 5ms
#define DIR_CONTROL_TIME		10u			//run direction control every 2ms
#define BALANCE_CONTROL_TIME	10u			//run balance control every 2ms
#define OLED_CHANGE_TIME		500u		//update oled display every 20ms
#define ELAPSE_TIME				1000u		//elapse time 20ms

#endif//INCLUDES_H_

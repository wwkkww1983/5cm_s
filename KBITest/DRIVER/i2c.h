/*
 *--------------------------------------------------------------------------------
 *	FileName		i2c.h	
 *	Brief			IIC module driver
 *	Microchip		KEA128
 *	Author			YTom
 *	E-mail			ybb331082@126.com
 *	ModifyTime		18-01-30 23:02
 *	Copyright 		2017 TU-Smart. All Rights Reserved.
 *	Info			i2c0_PinsGroup==0
						I2C0_SCL	(PTA3), I2C0_SDA	(PTA2)
					i2c0_PinsGroup==1
						I2C0_SCL	(PTB7), I2C0_SDA	(PTB6)
					i2c1_PinsGroup==0
						I2C1_SCL	(PTH4), I2C1_SDA	(PTH3)
					i2c1_PinsGroup==1
						I2C1_SCL	(PTE1), I2C1_SDA	(PTE0)
 *--------------------------------------------------------------------------------
 */
	
#ifndef I2C_H_
#define I2C_H_

#include "common.h"
#include "gpio.h"
#include "delay.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/** Defines
  * @brief Basic Setting
  */
#define i2c_SCL			(PORTB|7)
#define i2c_SDA			(PORTB|6)

#define i2c_HIGH		0
#define i2c_LOW			1

#define	i2c_Ack_Fail	1
#define	i2c_Ack_Succ	0

#define i2c_sendAck		0
#define i2c_sendNAck 	1

 /** Defines
  * @brief IO׽вʨ׃
  */
#define i2c_SDA_Mode_SetIN()  	gpio_setIn(i2c_SDA)
#define i2c_SDA_Mode_SetOUT() 	gpio_setOut(i2c_SDA)

//IOәطگ˽	 
//#define I2C_SCL    	PBout(I2C_SCL_PinNUM) 	//SCL
//#define I2C_SDA    	PBout(I2C_SDA_PinNUM) 	//SDA	 
//#define I2C_SDA_Read  PBin(I2C_SDA_PinNUM)  	//ˤɫSDA 
#define 	i2c_SCL_SetH		gpio_set(i2c_SCL,1)
#define 	i2c_SCL_SetL		gpio_set(i2c_SCL,0)
#define 	i2c_SDA_SetH		gpio_set(i2c_SDA,1)
#define 	i2c_SDA_SetL		gpio_set(i2c_SDA,0)
#define 	i2c_SDA_Read		gpio_get(i2c_SDA)
	
/** Function
  * @brief 
  */	
void 	i2c_InitConfig(void);                	//ԵʼۯIICքIOࠚ				 
void 	i2c_Start(void);						//ע̍IICߪʼхۅ
void 	i2c_Stop(void);	  						//ע̍IICֹͣхۅ
void 	i2c_Send_Byte(uint_8);					//IICע̍һٶؖޚ
uint_8 i2c_Read_Byte(unsigned char);			//IICׁȡһٶؖޚ
uint_8 i2c_Wait_Ack(void); 					//IICֈսACKхۅ
void 	i2c_Ack(void);							//IICע̍ACKхۅ
void 	i2c_NAck(void);							//IICһע̍ACKхۅ

//void 	I2C_Write_One_Byte(uint_8_t ,uint_8_t,uint_8_t);
//uint_8_t I2C_Read_One_Byte(uint_8_t, uint_8_t);	


#ifdef  __cplusplus
}
#endif

#endif

/**********************************END OF FILE**********************************/




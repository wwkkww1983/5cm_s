/*
 *--------------------------------------------------------------------------------
 *	FileName		accelerometer.c	
 *	Brief			Accelerometer(MMA8452Q) driver
 *	Microchip		KEA128
 *	Author			YTom
 *	E-mail			ybb331082@126.com
 *	ModifyTime		
 *	Copyright 		2017 TU-Smart. All Rights Reserved.
 *	Attention	
 *--------------------------------------------------------------------------------
 */
 
#include "accelerometer.h"

MMA_Mode MMA_Mode_Val;
MMA_Sensi MMA_Sensi_Val;

// INNER FUNCTION
uint_8 acce_readbyte(uint_8 addr, uint_8 subaddr);

/*
* brief : 	Initialize accelerometer(MMA8452Q) module
* param : 	mode	FREAD mode(MMA_12bit_Mode(normal) or MMA_8bit_Mode(fast))
*			sens	Sensitivity (MMA_Sensi_2g, MMA_Sensi_4g, MMA_Sensi_8g)
* return:	Statuss: MMA_Fail or MMA_Succ
* note	:	
*/
uint_8 acceInit(MMA_Mode mode, MMA_Sensi sens)
{
	uint_8 tmp;
	i2c_InitConfig();	// Baud is useless now
	
	tmp = acce_readbyte(MMA_ADDR, MMA_CTRL_REG1);
	acceWriteByte(MMA_ADDR, MMA_CTRL_REG1, tmp&~MMA_CTRLREG1_ACTIVE_MASK);	// STANDBY
	tmp = acce_readbyte(MMA_ADDR, MMA_CTRL_REG2);
	acceWriteByte(MMA_ADDR, MMA_CTRL_REG2, tmp|MMA_CTRLREG2_RST_MASK);	// Reset
	delay_ms(50);
	acceWriteByte(MMA_ADDR, MMA_XYZ_DATA_CFG, (uint_8)sens);	// Select sensitivity(NO FUNCTION)
	tmp = 0x00;
	acceWriteByte(MMA_ADDR, MMA_CTRL_REG1, tmp);				// Reset MMA_CTRL_REG1
	switch(mode){
		case MMA_8bit_Mode:
			tmp |= MMA_CTRLREG1_FREAD_MASK;
			break;
		default:
			tmp &= ~MMA_CTRLREG1_FREAD_MASK;
	}
	tmp |= MMA_CTRLREG1_DR(3)|MMA_CTRLREG1_LNOISE_MASK;			// 100Hz, LowNoise
	tmp |= MMA_CTRLREG1_ACTIVE_MASK;							// ACTIVE
	acceWriteByte(MMA_ADDR, MMA_CTRL_REG1, tmp);			
	MMA_Mode_Val = mode;
	MMA_Sensi_Val = sens;
	delay_ms(50);
	return MMA_Succ;
}

/*
* brief : 	Read or write byte data from accelerometer(MMA8452Q)
* param : 	addr		Module slave address
*			subaddr		Register address of the module
*			ret			Return value
*			data		Data for writing
* return:	Statuss: MMA_Fail or MMA_Succ
* note	:	
*/
// INNER FUNCTION
uint_8 acce_readbyte(uint_8 addr, uint_8 subaddr)
{
	uint_8 tmp;
	i2c_Start();
	i2c_Send_Byte((addr<<1)|0);				//·¢ËÍµØÖ·,Ð´ÃüÁî
	if(i2c_Wait_Ack()==i2c_Ack_Fail){
		return MMA_Fail;
	}
	i2c_Send_Byte(subaddr);					//·¢ËÍµØÖ·
	if(i2c_Wait_Ack()==i2c_Ack_Fail){
		return MMA_Fail;
	}
	i2c_Start();
	i2c_Send_Byte((addr<<1)|1);				//·¢ËÍµØÖ·,¶ÁÃüÁî
	if(i2c_Wait_Ack()==i2c_Ack_Fail){
		return MMA_Fail;
	}
	tmp=i2c_Read_Byte(i2c_sendNAck);
	i2c_Stop();
	return tmp;
}

uint_8 acceReadByte(uint_8 addr, uint_8 subaddr, uint_8* ret)
{
//	uint_8 tmp;
//	if((tmp = acce_readbyte(addr, subaddr))==MMA_Fail) {
//		return MMA_Fail;n
//	}
//	else{
//		*ret = tmp;
//		return MMA_Succ;
//	}
	*ret = acce_readbyte(addr, subaddr);
	return 0;
}

uint_8 acceWriteByte(uint_8 addr, uint_8 subaddr, uint_8 data)
{
	i2c_Start();
	i2c_Send_Byte((addr<<1)|0);				//·¢ËÍµØÖ·,Ð´ÃüÁî
	if(i2c_Wait_Ack()==i2c_Ack_Fail){
		return MMA_Fail;
	}
	i2c_Send_Byte(subaddr);					//·¢ËÍµØÖ·
	if(i2c_Wait_Ack()==i2c_Ack_Fail){
		return MMA_Fail;
	}
	i2c_Send_Byte(data);					//·¢ËÍÊý¾Ý
	if(i2c_Wait_Ack()==i2c_Ack_Fail){
		return MMA_Fail;
	}
	i2c_Stop();
	return MMA_Succ;
}

/*
* brief : 	Read or write some datas from accelerometer(MMA8452Q)
* param : 	addr		Module slave address
*			subaddr		Register address of the module
*			len			Data length
*			ret			Return values
*			data		Data for writing
* return:	Statuss: MMA_Fail or MMA_Succ
* note	:	
*/
uint_8 acceReadL(uint_8 addr, uint_8 subaddr, uint_8 len, uint_8* ret)
{
	uint_8 tmp;
	i2c_Start();
	i2c_Send_Byte((addr<<1)|0);				//·¢ËÍµØÖ·,Ð´ÃüÁî
	if(i2c_Wait_Ack()==i2c_Ack_Fail){
		return MMA_Fail;
	}
	i2c_Send_Byte(subaddr);					//·¢ËÍµØÖ·
	if(i2c_Wait_Ack()==i2c_Ack_Fail){
		return MMA_Fail;
	}
	i2c_Start();
	i2c_Send_Byte((addr<<1)|1);				//·¢ËÍµØÖ·,¶ÁÃüÁî
	if(i2c_Wait_Ack()==i2c_Ack_Fail){
		return MMA_Fail;
	}
	// Continously read
	tmp = 0;
	while(tmp<len-1){
		ret[tmp]=i2c_Read_Byte(i2c_sendAck);	// Read with ack
		tmp++;
	}
	ret[tmp]=i2c_Read_Byte(i2c_sendNAck);
	i2c_Stop();
	return MMA_Succ;
}

uint_8 acceWriteL(uint_8 addr, uint_8 subaddr, uint_8 len, uint_8* data)
{
	uint_8 tmp;
	i2c_Start();
	i2c_Send_Byte((addr<<1)|0);				//·¢ËÍµØÖ·,Ð´ÃüÁî
	if(i2c_Wait_Ack()==i2c_Ack_Fail){
		return MMA_Fail;
	}
	i2c_Send_Byte(subaddr);					//·¢ËÍµØÖ·
	if(i2c_Wait_Ack()==i2c_Ack_Fail){
		return MMA_Fail;
	}
	// Continously write
	tmp = 0;
	while(tmp<len){
		i2c_Send_Byte(data[tmp]);			//·¢ËÍÊý¾Ý
		if(i2c_Wait_Ack()==i2c_Ack_Fail){
			return MMA_Fail;
		}
		tmp++;
	}
	i2c_Stop();
	return MMA_Succ;
}

/*
* brief : 	Caculate the raw data to exact value
* param : 	mode	FREAD mode(MMA_12bit_Mode(normal) or MMA_8bit_Mode(fast))
*			input		Raw data array
*			output		Solved data array
* return:	None
* note	:	
*/
void acceSolveData(MMA_Mode mode, uint_8* input, int_16* output)
{
	int_16 tmp;
	tmp = ((int_16)((input[0]<<4)&0x0ff0))|((input[1]>>4)&0x0f);
	if(tmp>=2048) tmp=tmp-4096;
	output[0] = tmp;
	tmp = ((int_16)((input[2]<<4)&0x0ff0))|((input[3]>>4)&0x0f);
	if(tmp>=2048) tmp=tmp-4096;
	output[1] = tmp;
	tmp = ((int_16)((input[4]<<4)&0x0ff0))|((input[5]>>4)&0x0f);
	if(tmp>=2048) tmp=tmp-4096;;
	output[2] = tmp;
	
//	int8 tmp;
//	output[0] = (INT8)input[0];
//	output[1] = (INT8)input[2];
//	output[2] = (INT8)input[4];

}

/*-------------------------------INNER FUNCTIONS-------------------------------*/

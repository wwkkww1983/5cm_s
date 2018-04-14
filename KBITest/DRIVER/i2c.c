/*
 *--------------------------------------------------------------------------------
 *	FileName		i2c.c
 *	Brief			IIC module driver
 *	Microchip		KEA128
 *	Author			YTom
 *	E-mail			ybb331082@126.com
 *	ModifyTime		18-01-30 23:02
 *	Copyright 		2017 TU-Smart. All Rights Reserved.
 *	Attention	
 *--------------------------------------------------------------------------------
 */

/** Includes 
  * @brief
  */
#include "i2c.h"

void i2c_delay(uint_16 cnt){
	while(cnt--) __NOP();
}


/** Function
  * @brief 初始化IIC
  * @param
  * @retval
  */
void i2c_InitConfig(void)
{
	delay_Init(delay_CORE_CLK);
	gpio_init(i2c_SCL,GPIO_OUTPUT,i2c_HIGH);
	gpio_init(i2c_SDA,GPIO_OUTPUT,i2c_HIGH);
	//GPIO引脚初始化设置
	i2c_SCL_SetH;
	i2c_SDA_SetH;
}

/** Function
  * @brief 产生IIC起始信号
  * @param
  * @retval
  */
void i2c_Start(void)
{
	i2c_SDA_Mode_SetOUT();     //sda线输出
	i2c_SCL_SetH;
	i2c_SDA_SetH;
//	i2c_delay(4);
	delay_us(4);
 	i2c_SDA_SetL;		//START:when CLK is high,DATA change form high to low 
//	i2c_delay(4);
	delay_us(4);
	i2c_SCL_SetL;		//钳住i2c总线，准备发送或接收数据 
}	

/** Function
  * @brief 产生IIC停止信号
  * @param
  * @retval
  */
void i2c_Stop(void)
{
	i2c_SDA_Mode_SetOUT();//sda线输出
	i2c_SCL_SetL;
	i2c_SDA_SetL;		//STOP:when CLK is high DATA change form low to high
//	i2c_delay(4);
	delay_us(4);
	i2c_SCL_SetH;
	i2c_SDA_SetH;//发送i2c总线结束信号
//	i2c_delay(4);
	delay_us(4);							   	
}

/** Function
  * @brief 等待应答信号到来,返回值：0=接收应答失败,1=接收应答成功
  * @param
  * @retval
  */
uint_8 i2c_Wait_Ack(void)
{
	uint_8 ucErrTime=0;
	i2c_SDA_Mode_SetIN();      //SDA设置为输入  
	// Release I2C bus
	i2c_SDA_SetH;//	i2c_delay(1);
	delay_us(1);  
	i2c_SCL_SetH;//	i2c_delay(1);
	delay_us(1);
	while(i2c_SDA_Read)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			i2c_Stop();
			return i2c_Ack_Fail;
		}
	}
	i2c_SCL_SetL;	//时钟输出0 	   
	return i2c_Ack_Succ;  
} 

/** Function
  * @brief 生ACK应答
  * @param
  * @retval
  */
void i2c_Ack(void)
{
	i2c_SCL_SetL;
	i2c_SDA_Mode_SetOUT();
	i2c_SDA_SetL;
//	i2c_delay(2);
	delay_us(1);
	i2c_SCL_SetH;
//	i2c_delay(2);
	delay_us(1);
	i2c_SCL_SetL;
	i2c_SDA_SetH;	// Release SDA!!!
}

/** Function
  * @brief 不产生ACK应答
  * @param
  * @retval
  */    
void i2c_NAck(void)
{
	i2c_SCL_SetL;
	i2c_SDA_Mode_SetOUT();
	i2c_SDA_SetH;
//	i2c_delay(2);
	delay_us(1);
	i2c_SCL_SetH;
//	i2c_delay(2);
	delay_us(1);
	i2c_SCL_SetL;
	i2c_SDA_SetH;	// Release SDA!!!
}	

/** Function
  * @brief IIC发送一个字节,返回从机有无应答 1=有应答 0=无应答			  
  * @param
  * @retval
  */
void i2c_Send_Byte(uint_8 txd)
{                        
    uint_8 t;   
	i2c_SDA_Mode_SetOUT(); 	    
    i2c_SCL_SetL;//拉低时钟开始数据传输
    for(t=0x80;t!=0;t>>=1)
    {              
        if(txd&t)
			i2c_SDA_SetH;
		else
			i2c_SDA_SetL;
		//	i2c_delay(2);
		delay_us(2);   //对TEA5767这三个延时都是必须的
		i2c_SCL_SetH;
		//	i2c_delay(2);
		delay_us(2); 
		i2c_SCL_SetL;
		//	i2c_delay(2);
		delay_us(2);
    }	 
} 	

/** Function
  * @brief 读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
  * @param	ack i2c_sendAck or i2c_sendNAck
  * @retval
  */
uint_8 i2c_Read_Byte(unsigned char ack)
{
	uint_8 t, receive=0;
	i2c_SDA_Mode_SetIN();//SDA设置为输入
    for(t=0;t<8;t++)
    {
        receive<<=1;
		if(i2c_SDA_Read)
			receive++;
		//	i2c_delay(2);
		delay_us(2);   //对TEA5767这三个延时都是必须的
		i2c_SCL_SetH;
		//	i2c_delay(2);
		delay_us(2); 
		i2c_SCL_SetL;
		//	i2c_delay(2);
		delay_us(2);
    }
    if (ack==i2c_sendNAck)
        i2c_NAck();//发送nACK
    else
        i2c_Ack(); //发送ACK   
    return receive;
}

/**********************************END OF FILE**********************************/



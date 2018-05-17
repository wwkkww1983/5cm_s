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
  * @brief ��ʼ��IIC
  * @param
  * @retval
  */
void i2c_InitConfig(void)
{
	delay_Init(delay_CORE_CLK);
	gpio_init(i2c_SCL,GPIO_OUTPUT,i2c_HIGH);
	gpio_init(i2c_SDA,GPIO_OUTPUT,i2c_HIGH);
	//GPIO���ų�ʼ������
	i2c_SCL_SetH;
	i2c_SDA_SetH;
}

/** Function
  * @brief ����IIC��ʼ�ź�
  * @param
  * @retval
  */
void i2c_Start(void)
{
	i2c_SDA_Mode_SetOUT();     //sda�����
	i2c_SCL_SetH;
	i2c_SDA_SetH;
//	i2c_delay(4);
	delay_us(4);
 	i2c_SDA_SetL;		//START:when CLK is high,DATA change form high to low 
//	i2c_delay(4);
	delay_us(4);
	i2c_SCL_SetL;		//ǯסi2c���ߣ�׼�����ͻ�������� 
}	

/** Function
  * @brief ����IICֹͣ�ź�
  * @param
  * @retval
  */
void i2c_Stop(void)
{
	i2c_SDA_Mode_SetOUT();//sda�����
	i2c_SCL_SetL;
	i2c_SDA_SetL;		//STOP:when CLK is high DATA change form low to high
//	i2c_delay(4);
	delay_us(4);
	i2c_SCL_SetH;
	i2c_SDA_SetH;//����i2c���߽����ź�
//	i2c_delay(4);
	delay_us(4);							   	
}

/** Function
  * @brief �ȴ�Ӧ���źŵ���,����ֵ��0=����Ӧ��ʧ��,1=����Ӧ��ɹ�
  * @param
  * @retval
  */
uint_8 i2c_Wait_Ack(void)
{
	uint_8 ucErrTime=0;
	i2c_SDA_Mode_SetIN();      //SDA����Ϊ����  
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
	i2c_SCL_SetL;	//ʱ�����0 	   
	return i2c_Ack_Succ;  
} 

/** Function
  * @brief ��ACKӦ��
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
  * @brief ������ACKӦ��
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
  * @brief IIC����һ���ֽ�,���شӻ�����Ӧ�� 1=��Ӧ�� 0=��Ӧ��			  
  * @param
  * @retval
  */
void i2c_Send_Byte(uint_8 txd)
{                        
    uint_8 t;   
	i2c_SDA_Mode_SetOUT(); 	    
    i2c_SCL_SetL;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0x80;t!=0;t>>=1)
    {              
        if(txd&t)
			i2c_SDA_SetH;
		else
			i2c_SDA_SetL;
		//	i2c_delay(2);
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		i2c_SCL_SetH;
		//	i2c_delay(2);
		delay_us(2); 
		i2c_SCL_SetL;
		//	i2c_delay(2);
		delay_us(2);
    }	 
} 	

/** Function
  * @brief ��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
  * @param	ack i2c_sendAck or i2c_sendNAck
  * @retval
  */
uint_8 i2c_Read_Byte(unsigned char ack)
{
	uint_8 t, receive=0;
	i2c_SDA_Mode_SetIN();//SDA����Ϊ����
    for(t=0;t<8;t++)
    {
        receive<<=1;
		if(i2c_SDA_Read)
			receive++;
		//	i2c_delay(2);
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		i2c_SCL_SetH;
		//	i2c_delay(2);
		delay_us(2); 
		i2c_SCL_SetL;
		//	i2c_delay(2);
		delay_us(2);
    }
    if (ack==i2c_sendNAck)
        i2c_NAck();//����nACK
    else
        i2c_Ack(); //����ACK   
    return receive;
}

/**********************************END OF FILE**********************************/



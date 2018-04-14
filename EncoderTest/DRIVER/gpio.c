//===========================================================================
//文件名称：gpio.c
//功能概要：GPIO底层驱动构件源文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-01-28  V1.0
//芯片类型：KEA128
//作者： Shine Wong
//===========================================================================
#include "gpio.h"   //包含本构件头文件

uint_32 bit;    //内部变量，用于记录引脚在端口寄存器中的偏移量
//内部函数声明
static void gpio_port_pin_num(uint_16 port_pin,uint_8* port,uint_8* pin);

//===========================================================================
//函数名称：gpio_init
//函数返回：无
//参数说明：port_pin：(端口号)|(引脚号)（例：PORTB|(5) 表示为B口5号脚）
//       dir：引脚方向（0=输入，1=输出,可用引脚方向宏定义）
//       state：端口引脚初始状态（0=低电平，1=高电平）
//功能概要：初始化指定端口引脚作为GPIO引脚功能，并定义为输入或输出，若是输出，
//       还指定初始状态是低电平或高电平
//===========================================================================
void gpio_init(uint_16 port_pin, uint_8 dir, uint_8 state)
{
	//局部变量声明
	GPIO_MemMapPtr gpio_ptr;    //声明port_ptr为GPIO结构体类型指针
	uint_8 port;                //端口号
	uint_8 pin;                 //引脚号
	gpio_port_pin_num(port_pin, &port, &pin);   //解析出端口号及引脚号
	//计算引脚在寄存器中的偏移量
	if (port < 4)               //端口号为PORTA~PORTD
	{
		//端口所在的寄存器基地址
		gpio_ptr = GPIOA_BASE_PTR;
		//引脚所在的位数
		bit = 8 * port + pin;
	} 
	else if(3<port &&port< 8)   //端口号为PORTE~PORTH
	{
		//端口所在的寄存器基地址
		gpio_ptr = GPIOB_BASE_PTR;
		//引脚所在的位数
		bit = 8 * (port - 4) + pin;
	}
	else                        //端口号为PORTI
	{
		//端口所在的寄存器基地址
		gpio_ptr = GPIOC_BASE_PTR;
		//引脚所在的位数
		bit = 8 * (port - 8) + pin;
	}
	//根据带入参数dir，决定引脚为输出还是输入
	if (1 == dir)   //希望为输出
	{
		//数据方向寄存器定义为输出
		BSET(bit, GPIO_PDDR_REG(gpio_ptr));
		
		BSET(bit, GPIO_PCOR_REG(gpio_ptr));
		//初始状态为低电平
		gpio_set(port_pin, state);   //调用gpio_set函数，设定引脚初始状态
	} 
	else 
	{
		//希望为输入
		BCLR(bit, GPIO_PDDR_REG(gpio_ptr));
		BCLR(bit, GPIO_PIDR_REG(gpio_ptr));
	}
}

//===========================================================================
//函数名称：gpio_set
//函数返回：无
//参数说明：port_pin：端口号|引脚号（例：PORTB|(5) 表示为B口5号脚）
//       state：引脚初始状态（0=低电平，1=高电平）
//功能概要：设定引脚状态为低电平或高电平
//===========================================================================
void gpio_set(uint_16 port_pin, uint_8 state)
{
	//局部变量声明
	GPIO_MemMapPtr gpio_ptr;    //声明port_ptr为GPIO结构体类型指针
	uint_8 port;                //端口号
	uint_8 pin;                 //引脚号
	gpio_port_pin_num(port_pin, &port, &pin);   //解析出端口号及引脚号
	//计算引脚在寄存器中的偏移量
	if (port < 4)               //端口号为PORTA~PORTD
	{
		//端口所在的寄存器基地址
		gpio_ptr = GPIOA_BASE_PTR;
		//引脚所在的位数
		bit = 8 * port + pin;
	} 
	else if(3<port &&port< 8)   //端口号为PORTE~PORTH
	{
		//端口所在的寄存器基地址
		gpio_ptr = GPIOB_BASE_PTR;
		//引脚所在的位数
		bit = 8 * (port - 4) + pin;
	}
	else                        //端口号为PORTI
	{
		//端口所在的寄存器基地址
		gpio_ptr = GPIOC_BASE_PTR;
		//引脚所在的位数
		bit = 8 * (port - 8) + pin;
	}
	
	//根据带入参数state，决定引脚为输出1还是0
	if (1==state) {BSET(bit,gpio_ptr->PDOR);} else {BCLR(bit,gpio_ptr->PDOR);}
}

//===========================================================================
//函数名称：gpio_get
//函数返回：指定引脚的状态（1或0）
//参数说明：port_pin：端口号|引脚号（例：PORTB|(5) 表示为B口5号脚）
//功能概要：获取指定引脚的状态（1或0）
//===========================================================================
uint_8 gpio_get(uint_16 port_pin)
{
	//局部变量声明
	GPIO_MemMapPtr gpio_ptr;    //声明port_ptr为GPIO结构体类型指针
	uint_8 port;                //端口号
	uint_8 pin;                 //引脚号
	gpio_port_pin_num(port_pin, &port, &pin);   //解析出端口号及引脚号
	//计算引脚在寄存器中的偏移量
	if (port < 4)               //端口号为PORTA~PORTD
	{
		//端口所在的寄存器基地址
		gpio_ptr = GPIOA_BASE_PTR;
		//引脚所在的位数
		bit = 8 * port + pin;
	} 
	else if(3<port &&port< 8)   //端口号为PORTE~PORTH
	{
		//端口所在的寄存器基地址
		gpio_ptr = GPIOB_BASE_PTR;
		//引脚所在的位数
		bit = 8 * (port - 4) + pin;
	}
	else                       //端口号为PORTI
	{
		//端口所在的寄存器基地址
		gpio_ptr = GPIOC_BASE_PTR;
		//引脚所在的位数
		bit = 8 * (port - 8) + pin;
	}
	
	//返回引脚的状态
	return ((BGET(bit,gpio_ptr->PDIR))>=1 ? 1:0);
}

//===========================================================================
//函数名称：gpio_reverse
//函数返回：无
//参数说明：port_pin：端口号|引脚号（例：PORTB|(5) 表示为B口5号脚）
//功能概要：反转指定引脚输出状态。
//===========================================================================
void gpio_reverse(uint_16 port_pin)
{
	//局部变量声明
	GPIO_MemMapPtr gpio_ptr;    //声明port_ptr为GPIO结构体类型指针
	uint_8 port;                //端口号
	uint_8 pin;                 //引脚号
	gpio_port_pin_num(port_pin, &port, &pin);   //解析出端口号及引脚号
	//计算引脚在寄存器中的偏移量
	if (port < 4)               //端口号为PORTA~PORTD
	{
		//端口所在的寄存器基地址
		gpio_ptr = GPIOA_BASE_PTR;
		//引脚所在的位数
		bit = 8 * port + pin;
	} 
	else if(3<port &&port< 8)   //端口号为PORTE~PORTH
	{
		//端口所在的寄存器基地址
		gpio_ptr = GPIOB_BASE_PTR;
		//引脚所在的位数
		bit = 8 * (port - 4) + pin;
	}
	else                       //端口号为PORTI
	{
		//端口所在的寄存器基地址
		gpio_ptr = GPIOC_BASE_PTR;
		//引脚所在的位数
		bit = 8 * (port - 8) + pin;
	}
	//反转指定引脚输出状态
	BSET(bit,gpio_ptr->PTOR);
}

//===========================================================================
//函数名称：gpio_pull
//函数返回：无
//参数说明：port_pin：端口号|引脚号（例：PORTB|(5) 表示为B口5号脚）
//       pullselect：引脚上拉使能选择（ 0=上拉除能，1=上拉使能）
//功能概要：使指定引脚上拉高电平
//===========================================================================
void gpio_pull(uint_16 port_pin, uint_8 pullselect)
{
	//局部变量声明
	uint_8 port;                //端口号
	uint_8 pin;                 //引脚号
	gpio_port_pin_num(port_pin, &port, &pin);   //解析出端口号及引脚号
	//计算引脚在寄存器中的偏移量
	if (port < 4)               //端口号为PORTA~PORTD
	{
		//引脚所在的位数
		bit = 8 * port + pin;
		if (1==pullselect){BSET(bit,PORT_PUE0);}
			else {BCLR(bit,PORT_PUE0);}
	}
	else if(3<port &&port< 8)  //端口号为PORTE~PORTH
	{
		//引脚所在的位数
		bit = 8 * (port - 4) + pin;
		if (1==pullselect){BSET(bit,PORT_PUE1);}
			else {BCLR(bit,PORT_PUE1);}
	}
	else                       //端口号为PORTI
	{
		//引脚所在的位数
		bit = 8 * (port - 8) + pin;
		if (1==pullselect){BSET(bit,PORT_PUE2);}
			else {BCLR(bit,PORT_PUE2);}
	}
}

//----------------------以下为内部函数存放处----------------------------------------
//===========================================================================
//函数名称：gpio_port_pin_num
//函数返回：无
//参数说明：port_pin：端口号|引脚号（例：PORTB|(5) 表示为B口5号脚）
//       port：解析出的端口号
//		 pin:解析出的引脚号（0~8，实际取值由芯片的物理引脚决定）
//功能概要：将传进参数port_pin（例：PORTB|(5)）进行解析，得出具体端口号与引脚号，由port、pin传出。
//       例如，PORTB|(5)解析为*port=PORTB，*pin=5）。
//备        注：port,pin为传地址参数，目的是将结果带回，调用函数前，不需要赋值
//===========================================================================
static void gpio_port_pin_num(uint_16 port_pin,uint_8* port,uint_8* pin)
{
	*port = port_pin>>8;
	*pin = port_pin;
}
//----------------------------内部函数结束---------------------------------------

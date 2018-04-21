//===========================================================================
//文件名称：OLED.h
//功能概要：OLED模块配置头文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-02-26  V1.0
//芯片类型：KEAZ128
//作者：Shine Wong
//===========================================================================
#ifndef OLED_H_
#define OLED_H_

#include "gpio.h"
#include "common.h"

#define u8  unsigned char 
#define u32 unsigned int 

#define OLED_CMD  0	
#define OLED_DATA 1	
#define OLED_MODE 0

//************OLED引脚定义****************//

/****************时钟*********************/
#define OLED_SCLK (PORTB|(2))

/****************数据*********************/
#define OLED_SDIN (PORTB|(3))

/****************复位*********************/
#define OLED_RST  (PORTB|(1))

/****************数据/命令*********************/
#define OLED_DC   (PORTB|(0))

/****************片选*********************/
#define OLED_CS   (PORTE|(6))

//****************END*********************//

#define OLED_CS_Clr()   gpio_set(OLED_CS,0)
#define OLED_CS_Set()   gpio_set(OLED_CS,1)
#define OLED_RST_Clr()  gpio_set(OLED_RST,0)
#define OLED_RST_Set()  gpio_set(OLED_RST,1)
#define OLED_DC_Clr()   gpio_set(OLED_DC,0)
#define OLED_DC_Set()   gpio_set(OLED_DC,1)
#define OLED_SCLK_Clr() gpio_set(OLED_SCLK,0)
#define OLED_SCLK_Set() gpio_set(OLED_SCLK,1)
#define OLED_SDIN_Clr() gpio_set(OLED_SDIN,0)
#define OLED_SDIN_Set() gpio_set(OLED_SDIN,1)

#define SIZE 		8
//#define XLevelL		0x02
//#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
//#define X_WIDTH 	128
//#define Y_WIDTH 	64	   

//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
//void OLED_DrawPoint(u8 x,u8 y,u8 t);
//void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
//void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2);
void OLED_ShowString(u8 x,u8 y, int_8 *p);	 
//void OLED_Set_Pos(unsigned char x, unsigned char y);
//void OLED_ShowCHinese(u8 x,u8 y,u8 no);
//void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void dis_num(u8 n,u8 y,int a);

#endif  

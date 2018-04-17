//===========================================================================
//文件名称：display.h
//功能概要：显示屏显示头文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-03-20  V1.0
//芯片类型：KEAZ128
//作者：莫庸
//===========================================================================
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "OLED.h"

/*DISPLAY FLAGS: 'change flag','add flag','subtract flag'*/
#define IS_OLED_CHANGED  		((flag)&(0x01))
#define SET_CHANGE_FLAG()		((flag)|=(0x01))
#define CLR_CHANGE_FLAG()		((flag)&=(~0x01))
#define IS_OLED_ADD				((flag)&(0x02))
#define SET_ADD_FLAG()			((flag)|=(0x02))
#define CLR_ADD_FLAG()			((flag)&=(~0x02))
#define IS_OLED_SUBTRACT		((flag)&(0x04))
#define SET_SUBTRACT_FLAG()		((flag)|=(0x04))
#define CLR_SUBTRACT_FLAG()		((flag)&=(~0x04))

#define MIN(X,Y) (X>Y?Y:X)

#define DATANUM 4		//the number of datas to be displayed
#define MAXLINE 4		//the maximum number of lines that can be displayed on a single page
#define SENSOR_PAGE 3	//refer to pages displaying datas read from sensors and are always changing

typedef struct{
	int_8  argName[6];	//argument name
	int_16* argValue;	//argument value
	uint_8  delta;		//argument variation
}displayItem, *pdisplayItem;

//===========================================================================
//Function: To display all the items on the OLED screen
//Return: null
//Arguements: items: an array of struct displayItem which stores all the information
//			  to be displayed
//Others: null
//===========================================================================
void OLEDDisplay(pdisplayItem items);

//===========================================================================
//Function: To deal with global arguement 'page'
//Return: null
//Arguements: null
//Others: null
//===========================================================================
void pageUp(void);
void pageDown(void);

//===========================================================================
//Function: To deal with global arguement 'line'
//Return: null
//Arguements: null
//Others: null
//===========================================================================
void lineUp(void);
void lineDown(void);

//===========================================================================
//Function: To increse/decrese a data assigned by page and line 
//Return: null
//Arguements: null
//Others: null
//===========================================================================
void dataIncrement(void);
void dataDecrement(void);

#endif

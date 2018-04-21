//===========================================================================
//文件名称：display.h
//功能概要：显示屏显示头文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-03-20  V1.0
//芯片类型：KEAZ128
//作者：莫庸
//修改：YTom
//===========================================================================
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "OLED.h"

#define MIN(X,Y) (X>Y?Y:X)

#define DATANUM 		17		//the number of datas to be displayed
#define MAXLINE 		8		//the maximum number of lines that can be displayed on a single page
#define NAMELENGTH		5		//characters limit for argName

#define VARIABLE_PAGE	0		//refer to pages displaying changeable variables(limit in this page)
#define SENSOR_PAGE 	1		//refer to pages displaying datas read from sensors and are always changing
#define DATA0_PAGE		2		//refer to pages displaying common datas
#define DATA1_PAGE		3		//refer to pages displaying common datas
#define DATA2_PAGE		4		//refer to pages displaying common datas

#define PAGE_COUNT		4

typedef struct{
	int_8  	argName[NAMELENGTH+1];	//argument name
	int_16* argValue;		//argument value
	uint_8  delta;			//argument variation
	uint8_t	changeable:1;	//is value changeable
	uint8_t	sensorVal:1;	//is value for sensor
	uint8_t pageNum:6;		//display in which page
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
void pageSwitch(void);

//===========================================================================
//Function: To deal with global arguement 'line'
//Return: null
//Arguements: null
//Others: null
//===========================================================================
void lineSwitch(void);

//===========================================================================
//Function: To increse/decrese a data assigned by page and line 
//Return: null
//Arguements: null
//Others: null
//===========================================================================
void dataIncrement(void);
void dataDecrement(void);

#endif

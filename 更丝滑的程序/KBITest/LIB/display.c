//===========================================================================
//文件名称：display.c
//功能概要：显示屏显示源文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-03-20  V1.0
//芯片类型：KEAZ128
//作者：	莫庸
//修改：YTom
//===========================================================================
#include "display.h"

uint_8 focusLine=0, currPage=0, flag=0;
uint_8 dispLines[8] = {0xff};			//Current items for displaying
char spaces[] = "                 ";

/*DISPLAY FLAGS: 'change flag','add flag','subtract flag'*/
#define IS_OLED_ADD				((flag)&(0x01))
#define SET_ADD_FLAG()			((flag)|=(0x01))
#define CLR_ADD_FLAG()			((flag)&=(~0x01))

#define IS_OLED_SUBTRACT		((flag)&(0x02))
#define SET_SUBTRACT_FLAG()		((flag)|=(0x02))
#define CLR_SUBTRACT_FLAG()		((flag)&=(~0x02))

//===========================================================================
//Function: To display all the items on the OLED screen
//Return: null
//Arguements: items: an array of struct displayItem which stores all the information
//			  to be displayed
//Others: null
//===========================================================================
void OLEDDisplay(pdisplayItem items){
	static uint_8 index,row;
	//Add or sub value
	if(IS_OLED_ADD){
		CLR_ADD_FLAG();
		*(items[dispLines[focusLine]].argValue) += items[dispLines[focusLine]].delta;
	}else if(IS_OLED_SUBTRACT){
		CLR_SUBTRACT_FLAG();
		*(items[dispLines[focusLine]].argValue) -= items[dispLines[focusLine]].delta;
	}
	row = 0;
	for(index=0; (index<DATANUM); index++){
		if(items[index].pageNum == currPage){
			dispLines[row] = index;
			//display argument name
			items[index].argName[NAMELENGTH] = '\0';
			OLED_ShowString(0,row, items[index].argName);
			//display focused line of changeable value with sign '*'
			if(row==focusLine && items[index].changeable){
				OLED_ShowChar(48,row,'*');
			}else{
				OLED_ShowChar(48,row,' ');
			}
			//display number
			dis_num(0,row, (int)(*(items[index].argValue)));
			row++;
		}
		if(row==MAXLINE) break;
	}
	while(row<MAXLINE){
		dispLines[row] = 0xff;
		OLED_ShowString(0,row, spaces);
		row++;
	}
}
//===========================================================================
//Function: To deal with global arguement 'page'
//Return: null
//Arguements: null
//Others: null
//===========================================================================
void pageSwitch(void){
	//if this is already the last page, return to the first page
	currPage = (currPage+1)%PAGE_COUNT;
	focusLine = 0;
}
//===========================================================================
//Function: To deal with global arguement 'line'
//Return: null
//Arguements: null
//Others: null
//===========================================================================
void lineSwitch(void){
	//If this is the last line of the page lines, return to the first line
	focusLine++;
	if(focusLine==MAXLINE || dispLines[focusLine]==0xff){
		focusLine = 0;
	}
}
//===========================================================================
//Function: To increse/decrese a data assigned by page and line 
//Return: null
//Arguements: null
//Others: null
//===========================================================================
void dataIncrement(void){
	SET_ADD_FLAG();
}

void dataDecrement(void){
	SET_SUBTRACT_FLAG();
}

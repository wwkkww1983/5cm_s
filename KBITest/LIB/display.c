//===========================================================================
//文件名称：display.c
//功能概要：显示屏显示源文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-03-20  V1.0
//芯片类型：KEAZ128
//作者：莫庸
//===========================================================================
#include "display.h"

uint_8 page, line, flag = 1;
char spaces[] = "                   ";
//===========================================================================
//Function: To display all the items on the OLED screen
//Return: null
//Arguements: items: an array of struct displayItem which stores all the information
//			  to be displayed
//Others: null
//===========================================================================
void OLEDDisplay(pdisplayItem items){
	//refer to pages displaying datas read from sensors and are always changing
	if(page<=SENSOR_PAGE) SET_CHANGE_FLAG();
	//detect add or subtract action
	if(IS_OLED_ADD){
		SET_CHANGE_FLAG();
		*(items[line+page*4].argValue) += items[line+page*4].delta;
		CLR_ADD_FLAG();
	}
	if(IS_OLED_SUBTRACT){
		SET_CHANGE_FLAG();
		*(items[line+page*4].argValue) -= items[line+page*4].delta;
		CLR_SUBTRACT_FLAG();
	}

	//detect whether the screen datas have be updated
	if(IS_OLED_CHANGED){
		CLR_CHANGE_FLAG();
		uint_8 index;
		//OLED_Clear();

		for(index=0; (index<MAXLINE); index++){
			if((index+MAXLINE*page)>=DATANUM){
			OLED_ShowString(0,2*index, spaces);	
			}else{
				OLED_ShowString(0,2*index, items[index+MAXLINE*page].argName);
				//display '*'
				if(index==line)		OLED_ShowChar(56,2*index,'*');
				else 							OLED_ShowChar(56,2*index,' ');
			
				dis_num(0,2*index, *(items[index+MAXLINE*page].argValue));
			}
		}
	}
}

//===========================================================================
//Function: To deal with global arguement 'page'
//Return: null
//Arguements: null
//Others: null
//===========================================================================
void pageUp(void){
	//if this is already the last page, return to the first page
	if(page==((DATANUM-1)/MAXLINE)) page = 0;
	else page++;
	line = 0;
	SET_CHANGE_FLAG()	;
}

void pageDown(void){
	//if this is the first page, reverse to the last page
	if(page==0) page = (DATANUM-1)/MAXLINE;
	else page--;
	line = 0;
	SET_CHANGE_FLAG()	;
}

//===========================================================================
//Function: To deal with global arguement 'line'
//Return: null
//Arguements: null
//Others: null
//===========================================================================
void lineUp(void){
	//If this is the last line of the screen, return to the first line
	if(line==MIN(MAXLINE-1,DATANUM-4*page-1)) line = 0;
	else line++;
	SET_CHANGE_FLAG();
}

void lineDown(void){
	//If this is the first line of the screen, reverse to the last line
	if(line==0) line = MIN(MAXLINE-1,DATANUM-4*page-1);
	else line--;
	SET_CHANGE_FLAG()	;
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

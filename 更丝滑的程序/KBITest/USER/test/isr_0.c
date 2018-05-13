#include "KBI.h"
#include "OLED.h"

uint_8 text1[] = "keyboard1 pressed";
uint_8 text2[] = "keyboard2 pressed";
uint_8 text3[] = "keyboard3 pressed";
uint_8 text4[] = "keyboard4 pressed";
uint_8 text5[] = "keyboard5 pressed";
uint_8 text6[] = "keyboard6 pressed";

void KBI0_IRQHandler(){
	  static uint_8 index = 0;
	  delay_ms(100);
	  if(isKBIFlagSet(KBI_0)){
			  if(0x01<<26 & KBI0_SP){//Press5
					  delay_ms(100);
					  if(0x01<<26 & KBI0_SP){
					  index++;
				    OLED_Clear();
				    OLED_ShowString(0,1,text5);
					  dis_num(1,0,index);
						}
		    }
		    if(0x01<<27 & KBI0_SP){//Press6
					  delay_ms(100);
					  if(0x01<<26 & KBI0_SP){
				    OLED_Clear();
					  OLED_ShowString(0,0,text6);
						}
		    }
				
				
				KBIClear(KBI_0);
				delay_ms(100);
	  }
}

void KBI1_IRQHandler(){
	  delay_ms(100);
	  if(isKBIFlagSet(KBI_1)){
			  if(0x01<<16 & KBI1_SP){//Press1
					  delay_ms(100);
					  if(0x01<<16 & KBI1_SP){
				    OLED_Clear();
				    OLED_ShowString(0,1,text1);
						}
		    }
		    if(0x01<<17 & KBI1_SP){//Press2
					  delay_ms(100);
					  if(0x01<<17 & KBI1_SP){
				    OLED_Clear();
					  OLED_ShowString(0,0,text2);
						}
		    }
				if(0x01<<18 & KBI1_SP){//Press2
					  delay_ms(100);
					  if(0x01<<18 & KBI1_SP){
				    OLED_Clear();
					  OLED_ShowString(0,0,text3);
						}
		    }
				if(0x01<<19 & KBI1_SP){//Press2
					  delay_ms(100);
					  if(0x01<<19 & KBI1_SP){
				    OLED_Clear();
					  OLED_ShowString(0,0,text4);
						}
		    }
				
				KBIClear(KBI_1);
				delay_ms(100);
	  }
}
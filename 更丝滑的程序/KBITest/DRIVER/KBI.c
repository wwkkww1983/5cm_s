//===========================================================================
//文件名称：KBI.c
//功能概要：KBI键盘中断模块配置源文件
//版权所有：同济大学Tu_smart智能车队
//版本更新：2018-03-04  V1.0
//芯片类型：KEAZ128
//作者：Shine Wong
//===========================================================================
#include "KBI.h"

//===========================================================================
//Function: To initialize KBI module and select the appropriate edge as well
//          as whether you are going to use pullup resistor
//Return: None
//Arguements: KBIPort: should be given in form 'KBINum|port' e.g.KBI_0|(0)
//            edge: select the falling edge(FALLING) or rising edge(RISING) 
//            pullSelect: choose whether to enable pullup resistor(1) or not(0)
//Others: None
//===========================================================================
void KBIInit(uint_16 KBIPort, uint_8 edge, uint_8 pullSelect){
    uint_8 KBINum = KBIPort >> 8;
    uint_8 KBIpin = KBIPort;
    uint_16 port, pin;//actual port pin corresponding to the MCU

    switch(KBINum){
        case 0:
            //enable clock to KBI0 
            SIM->SCGC |= SIM_SCGC_KBI0_MASK; 
            //disable KBI_0 interrupt
            KBI0_SC &= ~KBI_SC_KBIE_MASK;
            //select edge
            if(edge==RISING) KBI0_ES |= (0x1u<<KBIpin);
            else KBI0_ES &= ~(0x1u<KBIpin);
            //select pullup resistor
            if(KBIpin<8) port = PORTA;
            else if(KBIpin<16) port = PORTB;
            else if(KBIpin<24) port = PORTC;
            else if(KBIpin<32) port = PORTD;
            else;//error
            pin = KBIpin % 8;
            gpio_pull(port|pin,pullSelect);
            //Enable the selected KBI pin
            KBI0_PE |= 0x1u << KBIpin;
            //Clear the KBI interrupt flag
            KBI0_SC |= KBI_SC_KBACK_MASK;
            //select the KBI Detection mode
            KBI0_SC |= KBI_SC_KBMOD_MASK;
            //Enable KBIx_SP field
            KBI0_SC &= ~KBI_SC_KBSPEN_MASK;
            //Clear KBIx_SP field
            KBI0_SC |= KBI_SC_RSTKBSP_MASK;
            //Enable interrupt
            NVIC_EnableIRQ(KBI0_IRQn);
            KBI0_SC |= KBI_SC_KBIE_MASK;
            break;

        case 1:
            //enable clock to KBI1 
            SIM->SCGC |= SIM_SCGC_KBI1_MASK; 
            //disable KBI_1 interrupt
            KBI1_SC &= ~KBI_SC_KBIE_MASK;
            //select edge
            if(edge) KBI1_ES |= (0x1u<<KBIpin);
            else KBI1_ES &= ~(0x1u<KBIpin);
            //select pullup resistor
            if(KBIpin<8) port = PORTE;
            else if(KBIpin<16) port = PORTF;
            else if(KBIpin<24) port = PORTG;
            else if(KBIpin<32) port = PORTH;
            else;//error
            pin = KBIpin % 8;
            gpio_pull(port|pin,pullSelect);
            //Enable the selected KBI pin
            KBI1_PE |= 0x1u << KBIpin;
            //Clear the KBI interrupt flag
            KBI1_SC |= KBI_SC_KBACK_MASK;
            //select the KBI Detection mode
            KBI1_SC &= ~KBI_SC_KBMOD_MASK;
            //Enable KBIx_SP field
            KBI1_SC &= ~KBI_SC_KBSPEN_MASK;
            //Clear KBIx_SP field
            KBI1_SC |= KBI_SC_RSTKBSP_MASK;
            //Enable interrupt
            NVIC_EnableIRQ(KBI1_IRQn);
            KBI1_SC |= KBI_SC_KBIE_MASK;
            break;

        default://error
            break;
    }
}

//===========================================================================
//Function: To clear the interrupt flag as well as the KBIx_SP field
//Return: None
//Arguements: KBINum: select KBI_0 or KBI_1
//Others: This function should be used in the interrupt handler function
//===========================================================================
void KBIClear(uint_16 KBINum){
	switch(KBINum>>8){
		case 0://KBI_0
		    //Clear the KBI interrupt flag
            KBI0_SC |= KBI_SC_KBACK_MASK;
            //Clear KBIx_SP field
            KBI0_SC |= KBI_SC_RSTKBSP_MASK;
		    break;

		case 1://KBI_1
		    //Clear the KBI interrupt flag
            KBI1_SC |= KBI_SC_KBACK_MASK;
            //Clear KBIx_SP field
            KBI1_SC |= KBI_SC_RSTKBSP_MASK;
		    break;
	}
}

//===========================================================================
//Function: To detect whether KBI flag is set
//Return: True when the interrupt flag is set
//Arguements: KBINum: select KBI_0 or KBI_1
//Others: This function should be used in the interrupt handler function
//===========================================================================
uint_8 isKBIFlagSet(uint_16 KBINum){
	switch(KBINum>>8){
		case 0://KBI_0
		    return KBI_SC_KBF_MASK & KBI0_SC;
		
		case 1://KBI_1
		    return KBI_SC_KBF_MASK & KBI1_SC;
	}
	return 0;
}

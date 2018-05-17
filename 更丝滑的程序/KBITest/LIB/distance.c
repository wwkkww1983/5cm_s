#include "ADC.h"
#include "distance.h"

uint_8 DISTANCE_FLAGS;
/*
float Fil[10]={0.7,0.05,0.04,0.04,0.04,0.04,0.03,0.03,0.02,0.01};
int_16 Data_Res[5][10],Data_New[5]={0,0,0,0,0};
*/
int x_save[2]={2500},X,max=0,min=0,Max=8,aus_count=0,K=10;

void ADC_Read(int_16 Data_Res[][10]){  
	uint_8 i,j;
	for(i=9;i>0;i--){																//为新数据腾出位置
		for(j=0;j<10;j++)
			Data_Res[j][i]=Data_Res[j][i-1];
	}
	Data_Res[0][0]=ADCReadn(ADC_1,8);																		//载入最新值
	Data_Res[1][0]=ADCReadn(ADC_2,8);
	Data_Res[2][0]=ADCReadn(ADC_3,8);
	Data_Res[3][0]=ADCReadn(ADC_4,8);
	Data_Res[4][0]=ADCReadn(ADC_5,8);
	Data_Res[5][0]=ADCReadn(ADC_6,8);
	Data_Res[6][0]=ADCReadn(ADC_7,8);
	Data_Res[7][0]=ADCReadn(ADC_8,8);
	Data_Res[8][0]=ADCReadn(ADC_9,8);
	Data_Res[9][0]=ADCReadn(ADC_10,8);
}

void ADC_Smoothing(int_16 Data_Res[][10],int_16 Data_New[],float Fil[]){
	for(uint_8 i=0;i<10;i++){
		Data_New[i]=0;
		for(uint_8 j=0;j<10;j++){
			Data_New[i]+=Fil[j]*Data_Res[i][j];
		}
	}
}

int_16 getX(int_16 Data_New[]){
//
//	if(Data_New[5]<40&&Data_New[6]<40)																//斜电感出线条件
//		SET_FRONT_OUTOFLINE_FLAG();
//	else 
//		CLR_FRONT_OUTOFLINE_FLAG();
//	if(SLOPE_ACTIVE_FLAG&&Data_New[1]>SLOPE_lim1&&Data_New[2]>SLOPE_lim2&&Data_New[3]>SLOPE_lim1)							//坡道条件
//	{
//		  SET_SLOPE_FLAG();CLR_SLOPE_ACTIVE_FLAG();
//	}
	int_16 x=0;
	uint_8 i=0;
	for(;i<5;i++){																	//得到最大值和最小值数组序号
		if(Data_New[i]>Data_New[max]) max=i; 
		if(Data_New[i]<Data_New[min]) min=i;
	}
	/*if(Data_New[max]<ausValue)																//前排五个电感出线条件
		SET_SIDE_OUTOFLINE_FLAG();*/
	if(!CIRCLE_FLAG){															//常规赛道元素下位置偏差计算 
		CLR_SIDE_OUTOFLINE_FLAG();
		aus_count=0;
		if(max==0) 			x=1000-(10000*(float)(Data_New[0]-Data_New[1])/(Data_New[0]+Data_New[1]));	
		else if(max==4) x=4000+(10000*(float)(Data_New[4]-Data_New[3])/(Data_New[3]+Data_New[4]));	
		else{
			if(Data_New[max-1]>Data_New[max+1])
				x=max*1000+500.0*((Data_New[max]-Data_New[max-1]))/((Data_New[max]-Data_New[max+1]));				  
			else 
				x=(max+1)*1000-500.0*((Data_New[max]-Data_New[max+1]))/((Data_New[max]-Data_New[max-1]));	
		}
	 //x=5000-x;//yang																//坐标反转
		if(x-x_save[1]>1000)			x=x_save[1]+1000;											//保证偏差连续
		if(x_save[1]-x>1000)			x=x_save[1]-1000;
  }
	i=0;
	while(i<1){
		x_save[i]=x_save[i+1];	
		i++;		
	}
	if(x>2500)			X=x-2500;
	else 						X=2500-x;
	x_save[1]=x;
	
	return x;
}







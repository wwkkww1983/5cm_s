#include "ADC.h"
#include "distance.h"



uint_8 DISTANCE_FLAGS;
float Data_Res[5][10],Data_New[5]={0,0,0,0,0},Fil[10]={0.7,0.05,0.04,0.04,0.04,0.04,0.03,0.03,0.02,0.01};
int x_save[50]={2500},x=0,X,max=0,min=0,Max=8,aus_count=0,K=10;
int C_Lmax=190,	C_lmax=190,
	C_Up=100,	c_Up=190,
	SLOPE_lim1=300,SLOPE_lim2=350,
	ausValue=75;




void ADC_Read(float Data_Res[][10])
	{  
	int i,j;
	for(i=9;i>0;i--)																//为新数据腾出位置
	{
		for(j=0;j<5;j++)
			Data_Res[j][i]=Data_Res[j][i-1];
	}
	Data_Res[0][0]=ADCReadn(ADC_1,8);																		//载入最新值
	Data_Res[1][0]=ADCReadn(ADC_2,8);
	Data_Res[2][0]=ADCReadn(ADC_3,8);
	Data_Res[3][0]=ADCReadn(ADC_4,8);
	Data_Res[4][0]=ADCReadn(ADC_5,8);
}

void ADC_Smoothing(float Data_Res[][10],float Data_New[],float Fil[])
{
	for(int i=0;i<5;i++)
	{
		Data_New[i]=0;
		for(int j=0;j<10;j++)
		{
			Data_New[i]+=Fil[j]*Data_Res[i][j];
		}
	}
}

void DataAnalyze(float Data_New[])
{
	if(Data_New[5]<40&&Data_New[6]<40)																//斜电感出线条件
		SET_FRONT_OUTOFLINE_FLAG;
	else 
		CLR_FRONT_OUTOFLINE_FLAG;
//	if(Data_New[7]<20&&Data_New[8]<20&&Data_New[9]<20)													//环岛出线条件
//		circle_aus=1;
//	else 
//		circle_aus=0;
//	for(int i=0;i<5;i++)																	//得到最大值和最小值数组序号
//	{
//		if(Data_New[i]>Data_New[max])
//			max=i; 
//		if(Data_New[i]<Data_New[min])
//			min=i;
//	} 
//	if(Data_New[max]>800)																	//电感断线保护（禁止发车）
//		Press_Flag=1;
	if(SLOPE_ACTIVE_FLAG&&Data_New[1]>SLOPE_lim1&&Data_New[2]>SLOPE_lim2&&Data_New[3]>SLOPE_lim1)							//坡道条件
	{
		  SET_SLOPE_FLAG;CLR_SLOPE_ACTIVE_FLAG;
	}
//	if(!SLOPE_FLAG&&!CIRCLE_FLAG)														//环岛条件
//	{
//		if(Data_New[max]<C_Up&&Data_New[5]<c_Up&&Data_New[6]<c_Up&&Data_New[5]>50&&Data_New[6]>50)
//		{ 
//			if(ghgSwitch) 															//进入第一个环岛后开启干簧管检测
//				ghg_active=1;
//			CIRCLE_FLAG=1;//auscircle_active=1;
//			stop=1;
//			start=1;
//			restarttime=0;
//			time=0;
//		}  
//	}
	if(Data_New[max]<ausValue)																//前排五个电感出线条件
		SET_SIDE_OUTOFLINE_FLAG;
	else if(!CIRCLE_FLAG)															//常规赛道元素下位置偏差计算
	{ 
		CLR_SIDE_OUTOFLINE_FLAG;
		aus_count=0;
		if(max==0) 
			x=1000-(10000*(float)(Data_New[0]-Data_New[1])/(Data_New[0]+Data_New[1]));	
		else if(max==4) 
			x=4000+(10000*(float)(Data_New[4]-Data_New[3])/(Data_New[3]+Data_New[4]));	
		else 
		{
			if(Data_New[max-1]>Data_New[max+1])				
				x=max*1000+500.0*((Data_New[max]-Data_New[max-1]))/((Data_New[max]-Data_New[max+1]));				  
			else 
				x=(max+1)*1000-500.0*((Data_New[max]-Data_New[max+1]))/((Data_New[max]-Data_New[max-1]));	
		}
	 //x=5000-x;//yang																//坐标反转
		if(x-x_save[49]>1000)														//保证偏差连续
			x=x_save[49]+1000;
		if(x_save[49]-x>1000)
			x=x_save[49]-1000;
  }
//	if(CIRCLE_FLAG)																	//环岛内用近处三个电感计算位置偏差
//	{
//		for(i=7;i<10;i++)
//			if(Data_New[i]>Data_New[Max])
//				Max=i; 
//		if(Max==9) 
//			x=1500-6*(1000*(float)(Data_New[9]-Data_New[8])/(Data_New[8]+Data_New[9]));	
//		else if(Max==7) 
//			 x=3500+6*(1000*(float)(Data_New[7]-Data_New[8])/(Data_New[8]+Data_New[7]));	
//		else 
//		{
//			if(Data_New[Max-1]>Data_New[Max+1])				
//				x=3500-1000*((Data_New[Max]-Data_New[Max-1]))/((Data_New[Max]-Data_New[Max+1]));				  
//			else 
//				x=1500+1000*((Data_New[Max]-Data_New[Max+1]))/((Data_New[Max]-Data_New[Max-1]));	
//		}
//	}
//	if(x<-2000) 																	//位置偏差限幅
//		x=-2000;	
//	if (x>7000)  
//		x=7000;
//	i=0;
//	while(i<49)
//	{
//		x_save[i]=x_save[i+1];	
//		i++;		
//	}
//	if(x>2500) 
//		X=x-2500;
//	else 
//		X=2500-x;
//	x_save[49]=x;
//	if(auscircle_active)															//出环岛预处理
//	{
//		if(circle_angle==350&&Data_New[5]>C_lmax)
//			pre_aus=1;
//		if(circle_angle==-350&&Data_New[6]>C_lmax)
//			pre_aus=1;
//	}
//	if(auscircle_active&&Data_New[max]>C_Lmax)												//确定已经出环岛
//	{	
//		CIRCLE_FLAG=0;
//		auscircle_active=0;
//		auscircle++;
//		pre_aus=0;
//	}
}







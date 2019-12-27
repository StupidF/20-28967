#include "Ultrasonic.h"
#include <stdio.h>
#include "delay.h"
#include "led.h"
#include "uart.h"

unsigned int  time=0;
float         S=0;
unsigned int  Dist = 0;
bit           flag =0;

unsigned int aaa[5];

/********************************************************/
void  StartModule() 	   //触发测量	         
{
	TH0 = TL0 = 0;
	TX  = 1;			            
	Delay15us();
	TX  = 0;
}
/********************************************************/
unsigned int Conut()
{
	uint tempS;
	StartModule();		//测量距离
	while(!RX)
	{
		if(flag == 1)		    //超出测量
		{
			break;
		}
	}			//当RX为零时等待
	TR0 = 1;			    //开启计数
	while(RX)
	{	
		if(flag == 1)		    //超出测量
		{
			break;
		}		//当RX为1计数并等待
	}
	TR0  = 0;				//关闭计数
	time = TH0*256 + TL0;
	TH0 = 0;
	TL0 = 0;
	S = ( time * 1.87 ) / 100 ;  
	tempS = (uint)S;
	if(flag == 1)		    //超出测量
	{
		flag = 0;
	}
	
	Dist = (unsigned int )S;
	
	return Dist;
}

//unsigned int GetDIS(void)
//{
//	return Dist;
//}

/*******************************************************************************
* 函数名 : Timer0Init
* 描述   : 定时器0初始化，
* 输入   : 
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/
void Timer0Init(void)
{
	SCON=0x50;
	AUXR &= 0x7F;	//定时器时钟12T模式
	TMOD &= 0xF0;
	TMOD |= 0x01;	//设置定时器模式
	TL0 = 0;		//设置定时初值
	TH0 = 0;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 0;		//定时器0开始计时  
	ET0 = 1;
}
void Ultrasonic_Init()
{
	Timer0Init();
}

///********************************************************/
void zd0() interrupt 1 		 //T0中断用来计数器溢出,超过测距范围
{
	flag=1;							 //中断溢出标志
}

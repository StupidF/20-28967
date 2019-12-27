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
void  StartModule() 	   //��������	         
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
	StartModule();		//��������
	while(!RX)
	{
		if(flag == 1)		    //��������
		{
			break;
		}
	}			//��RXΪ��ʱ�ȴ�
	TR0 = 1;			    //��������
	while(RX)
	{	
		if(flag == 1)		    //��������
		{
			break;
		}		//��RXΪ1�������ȴ�
	}
	TR0  = 0;				//�رռ���
	time = TH0*256 + TL0;
	TH0 = 0;
	TL0 = 0;
	S = ( time * 1.87 ) / 100 ;  
	tempS = (uint)S;
	if(flag == 1)		    //��������
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
* ������ : Timer0Init
* ����   : ��ʱ��0��ʼ����
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void Timer0Init(void)
{
	SCON=0x50;
	AUXR &= 0x7F;	//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;
	TMOD |= 0x01;	//���ö�ʱ��ģʽ
	TL0 = 0;		//���ö�ʱ��ֵ
	TH0 = 0;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 0;		//��ʱ��0��ʼ��ʱ  
	ET0 = 1;
}
void Ultrasonic_Init()
{
	Timer0Init();
}

///********************************************************/
void zd0() interrupt 1 		 //T0�ж��������������,������෶Χ
{
	flag=1;							 //�ж������־
}

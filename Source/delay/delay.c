#include	"delay.h"
#include   <intrins.h>
//========================================================================
// ����: void  delay_ms
// ����: ��ʱ������
// ����: ms,Ҫ��ʱ��ms��, ����ֻ֧��20*256ms.
// ����: none.
// �汾: VER1.0
// ����: 2013-4-1
// ��ע: 
//========================================================================
void delay_ms(unsigned int ms)
{
	unsigned int i,j;
	for(i=0;i<ms;i++)
		for(j=0;j<123;j++) ;
}


void Delay15us()		//@11.0592MHz
{
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_();
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_();
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_();
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_();
	_nop_(); 
}



void delay(unsigned int i)
{
	while(i--);
}


//****************************************************
//DS18B20��ʱ����
//****************************************************
void delay2us(void)   //��� -0.010706018519us
{
    unsigned char a;
    for(a=4;a>0;a--);
}
 
void delay5us(void)   //��� -0.026765046296us
{
    unsigned char a;
    for(a=12;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}

void delay10us(void)   //��� -0.053530092593us
{
    unsigned char a;
    for(a=26;a>0;a--);
}
 
void delay60us(void)   //��� -0.049913194444us
{
    unsigned char a;
    for(a=164;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}
 
void delay500us(void)   //��� -0.054253472222us
{
    unsigned char a,b;
    for(b=251;b>0;b--)
        for(a=4;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}
//void delay1ms(void)   //��� 0us
//{
//    unsigned char a,b,c;
//    for(c=1;c>0;c--)
//        for(b=222;b>0;b--)
//            for(a=12;a>0;a--);
//}

void delay5ms(void)   //��� -0.000000000001us
{
    unsigned char a,b;
    for(b=97;b>0;b--)
        for(a=141;a>0;a--);
}

void delay180ms(void)   //��� -0.000000000023us
{
    unsigned char a,b,c;
    for(c=115;c>0;c--)
        for(b=84;b>0;b--)
            for(a=50;a>0;a--);
}





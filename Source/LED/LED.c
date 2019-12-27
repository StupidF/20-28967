#include "led.h"

unsigned char code fseg[]	=	{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char code segbit[]	=	{0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
unsigned char  disbuf[8]	=	{0,0,0,0,0,0,0,0};

 //-----------------------------------------------------------------------------
//// 函数原形定义
//#define uchar unsigned char

//void LED4_Display(void);			// LED显示
//void LED_OUT(uchar X);				// LED单字节串行移位函数

//unsigned char code LED_0F[];		// LED字模表
unsigned char LED[8];	//用于LED的8位显示缓存

unsigned char code LED_0F[] = 
{// 0	 1	  2	   3	4	 5	  6	   7	8	 9	  A	   b	C    d	  E    F    -
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf
};

sbit DIO 	= P1^6;				//串行数据输入
sbit RCLK  	= P1^5;				//时钟脉冲信号——上升沿有效
sbit SCLK 	= P1^4;				//打入信号————上升沿有效

//-----------------------------------------------------------------------------
// 全局变量


void LED_OUT(unsigned int X)
{
	u8 i;
	for(i=8;i>=1;i--)
	{
		if (X&0x80) 
			DIO=1; 
		else 
			DIO=0;
		X	<<=	1;
		SCLK = 	0;
		SCLK = 	1;
	}
}


void LED4_Display (void)
{
	unsigned char code *led_table;          // 查表指针
	u8 i;
	//显示第1位
	led_table = LED_0F + LED[0];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x01);		

	RCLK = 0;
	RCLK = 1;
	//显示第2位
	led_table = LED_0F + LED[1];
	i = *led_table;

	LED_OUT(i);		
	LED_OUT(0x02);		

	RCLK = 0;
	RCLK = 1;
	//显示第3位
	led_table = LED_0F + LED[2];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x04);	

	RCLK = 0;
	RCLK = 1;
	//显示第4位
	led_table = LED_0F + LED[3];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x08);		

	RCLK = 0;
	RCLK = 1;
	//显示第5位
	led_table = LED_0F + LED[4];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x10);	

	RCLK = 0;
	RCLK = 1;
	//显示第6位
	led_table = LED_0F + LED[5];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x20);	

	RCLK = 0;
	RCLK = 1;
	//显示第7位
	led_table = LED_0F + LED[6];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x40);	

	RCLK = 0;
	RCLK = 1;
	//显示第8位
	led_table = LED_0F + LED[7];
	i = *led_table;

	LED_OUT(i);		
	LED_OUT(0x80);	

	RCLK = 0;
	RCLK = 1;
}

void display(unsigned char *a) 
{
	unsigned char i;
	for(i=0;i<8;i++)
		LED[i] = a[i];
	LED4_Display();
} 


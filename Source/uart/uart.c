#include "uart.h"

#define S2RI 0x01   //串口2接收中断请求标志位  
#define S2TI 0x02   //串口2发送中断请求标志位 

#define FOSC 11059200L      //System frequency
#define BAUD 9600           //UART baudrate

void Uart1Init(void) //9600bps
{   
	TMOD=0x21;		   //设T0为方式1，GATE=1；
	SCON=0x50;
	TH0=0;
	TL0=0; 
	TR0=1;  
	ET0=1;             //允许T0中断
	TR1=1;			   //开启定时器
	TI=1;
	EA=1;			   //开启总中断
	TH1=0xFD;
	TL1=0xFD;
	ET1 = 0;		//禁止定时器1中断
    EA =1;        	//开总中断
    ES =1;        	//开串口1中断
    S2CON = 0x50;   //串口2工作在方式1  10位异步收发 S2REN=1允许接收
    BRT = 0xFD;     //独立波特率发生器初值
    AUXR = 0x10;    //BRTR=1 独立波特率发生器开始计数
    IE2 =0x01;      //开串口2中断  ES2=1
}
/*----------------------------
UART1 发送串口数据
-----------------------------*/
void UART1_SendData(unsigned char c)
{
	SBUF = c;  
	while(!TI);    //若TI=0，在此等待  
	TI = 0;    
}


/*----------------------------
UART1 发送字符串
-----------------------------*/
void UART1_SendString(unsigned char *s)
{
	while(*s !='\0')//检测字符串结束符
	{
		UART1_SendData(*s++);//发送当前字符
	}
}

/*----------------------------
UART2 发送串口数据
-----------------------------*/
void UART2_SendData(u8 c)
{
	S2BUF = c;  
	while(!(S2CON&S2TI));  //若S2TI=0，在此等待  
	S2CON&=~S2TI;     //S2TI=0    
}


/*----------------------------
UART1 发送字符串
-----------------------------*/
void UART2_SendString(char *s)
{
	while(*s !='\0')//检测字符串结束符
	{
		UART2_SendData(*s++);//发送当前字符
	}
}




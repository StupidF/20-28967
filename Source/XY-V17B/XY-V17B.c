#include "XY-V17B.h"
#include "uart.h"



unsigned char  WebSendCount = 1;
unsigned char  WebSendPos   = 0;
unsigned char  ZigbeeUartSend[15];
unsigned char  ZigbeeUartSend_oled[10];
unsigned char  TF_Mode[]       = {0xaa, 0x0B, 0x01, 0x01, 0xB7, 0XFF };
unsigned char  COMD_Play[]     = {0xAA, 0x1B, 0x00, 0XAC, 0XFF       };
unsigned char  COMD_Stop[]     = {0xaa, 0x04, 0x00, 0xae, 0XFF       };	//
unsigned char  COMD_panfu[]    = {0xaa, 0x09, 0x00, 0xB3, 0XFF       };   //盘符查询
unsigned char  COMD_VOL []     = {0xaa, 0x13, 0x01, 0x00, 0xD2, 0XFF };
unsigned char  COMD_Play_1[]   = {0xAA, 0x07, 0x02, 0X00, 0x01, 0xB4,0XFF };
unsigned char  COMD_Play_2[]   = {0xAA, 0x07, 0x02, 0X00, 0x02, 0xB5,0XFF };
unsigned char  COMD_Play_3[]   = {0xAA, 0x07, 0x02, 0X00, 0x03, 0xB6,0XFF };
unsigned char  COMD_Play_4[]   = {0xAA, 0x07, 0x02, 0X00, 0x04, 0xB7,0XFF };
unsigned char  COMD_Play_5[]   = {0xAA, 0x07, 0x02, 0X00, 0x05, 0xB8,0XFF };
unsigned char  COMD_Play_6[]   = {0xAA, 0x07, 0x02, 0X00, 0x06, 0xB9,0XFF };
unsigned char  COMD_Play_7[]   = {0xAA, 0x07, 0x02, 0X00, 0x07, 0xBA,0XFF };
unsigned char  COMD_Play_8[]   = {0xAA, 0x07, 0x02, 0X00, 0x08, 0xBB,0XFF };
unsigned char  COMD_Play_9[]   = {0xAA, 0x07, 0x02, 0X00, 0x09, 0xBC,0XFF };
unsigned char  COMD_Play_10[]  = {0xAA, 0x07, 0x02, 0X00, 0x0A, 0xBD,0XFF };
unsigned char  COMD_Play_11[]  = {0xAA, 0x07, 0x02, 0X00, 0x0B, 0xBE,0XFF };



void XY_V17B_INIT(void)
{
	SCON=0x50;	    //串口选择模式1, 8-bit UART, 使能接收    
    TMOD|=0x20;     //用定时器1设置波特率
    TH1=0xFD;     
    TR1=1;           
	TI=1; 			//开启串口中断
	ES = 1;
	EA = 1;
}

void SOURCEvoice(unsigned char TEMPTURE )
{
	if(TEMPTURE<10 && TEMPTURE>0)	//小于10度
	{
		ZigbeeUartSend[0] = 0XAA;
		ZigbeeUartSend[1] = 0X1B;
		ZigbeeUartSend[2] = 0X06;		//长度
		ZigbeeUartSend[3] = 0X32;
		ZigbeeUartSend[4] = 0X31;		//第一段  ‘当前温度’
		ZigbeeUartSend[6] = 0X30;
		ZigbeeUartSend[7] = TEMPTURE%10+0X30;	//温度值
		ZigbeeUartSend[8] = 0X32;
		ZigbeeUartSend[9] = 0X32;       //第三段  ‘摄氏度’
		ZigbeeUartSend[10] = (ZigbeeUartSend[0]
							+ZigbeeUartSend[1]
							+ZigbeeUartSend[2]
							+ZigbeeUartSend[3]
							+ZigbeeUartSend[4]
							+ZigbeeUartSend[5]
							+ZigbeeUartSend[6]
							+ZigbeeUartSend[7]
							+ZigbeeUartSend[8]
							+ZigbeeUartSend[9])/256;		
		WebSendCount = 11; 
		WebSendPos=1;	
		ES = 1;
	}
	else if(TEMPTURE == 10)     //10度分开处理
	{
		ZigbeeUartSend[0] = 0XAA;
		ZigbeeUartSend[1] = 0X1B;
		ZigbeeUartSend[2] = 0X06;		//长度
		ZigbeeUartSend[3] = 0X32;
		ZigbeeUartSend[4] = 0X31;		//第一段  ‘当前温度’
		ZigbeeUartSend[5] = 0X31;		
		ZigbeeUartSend[6] = 0X30;       //第二段  温度
		ZigbeeUartSend[7] = 0X32;
		ZigbeeUartSend[8] = 0X32;       //第三段  ‘摄氏度’
		
		ZigbeeUartSend[8] = 0x32;
		ZigbeeUartSend[8] = 0x33;		//当前时间
		
		ZigbeeUartSend[9] = (ZigbeeUartSend[0]
							+ZigbeeUartSend[1]
							+ZigbeeUartSend[2]
							+ZigbeeUartSend[3]
							+ZigbeeUartSend[4]
							+ZigbeeUartSend[5]
							+ZigbeeUartSend[6]
							+ZigbeeUartSend[7]
							+ZigbeeUartSend[8])%256;		
		WebSendCount = 10; 
		WebSendPos=0;	
		while(WebSendPos<WebSendCount)
		{
			SBUF = ZigbeeUartSend[WebSendPos];
			WebSendPos++;			
			while(!TI);    //若TI=0，在此等待  
			TI = 0; 
		}
	}
	else if(TEMPTURE>=10 &&TEMPTURE<20)	//十到二十度
	{
		ZigbeeUartSend[0] = 0XAA;
		ZigbeeUartSend[1] = 0X1B;
		ZigbeeUartSend[2] = 0X06;		//长度
		ZigbeeUartSend[3] = 0X32;
		ZigbeeUartSend[4] = 0X31;		//当前温度
		ZigbeeUartSend[5] = 0X31;
		ZigbeeUartSend[6] = TEMPTURE%10+0x30;  //温度值
		ZigbeeUartSend[7] = 0X32;
		ZigbeeUartSend[8] = 0X32;       //第三段  ‘摄氏度’
		ZigbeeUartSend[9] = (ZigbeeUartSend[0]
							+ZigbeeUartSend[1]
							+ZigbeeUartSend[2]
							+ZigbeeUartSend[3]
							+ZigbeeUartSend[4]
							+ZigbeeUartSend[5]
							+ZigbeeUartSend[6]
							+ZigbeeUartSend[7]
							+ZigbeeUartSend[8])%256;
//		ZigbeeUartSend[10] = '\0';
//		UART1_SendString(ZigbeeUartSend);	
		WebSendCount = 10; 
		WebSendPos=0;
		while(WebSendPos<WebSendCount)
		{
			SBUF = ZigbeeUartSend[WebSendPos];
			WebSendPos++;			
			while(!TI);    //若TI=0，在此等待  
			TI = 0; 
		}
	}
	else 
	{
		ZigbeeUartSend[0]  = 0XAA;
		ZigbeeUartSend[1]  = 0X1B;
		ZigbeeUartSend[2]  = 0X08;  //长度
		ZigbeeUartSend[3]  = 0X32;
		ZigbeeUartSend[4]  = 0X31;		//当前温度
		ZigbeeUartSend[5]  = 0X30;
		ZigbeeUartSend[6]  = TEMPTURE/10+0x30;	//温度值
		ZigbeeUartSend[7]  = 0X31;
		ZigbeeUartSend[8]  = TEMPTURE%10 +0x30;
		ZigbeeUartSend[9]  = 0X32;
		ZigbeeUartSend[10] = 0X32;       //第三段  ‘摄氏度	
		ZigbeeUartSend[11] = (ZigbeeUartSend[0]
							+ZigbeeUartSend[1]
							+ZigbeeUartSend[2]
							+ZigbeeUartSend[3]
							+ZigbeeUartSend[4]
							+ZigbeeUartSend[5]
							+ZigbeeUartSend[6]
							+ZigbeeUartSend[7]
							+ZigbeeUartSend[8]
							+ZigbeeUartSend[9]
							+ZigbeeUartSend[10])%256;			
		WebSendCount = 12; 
		WebSendPos=0;
		while(WebSendPos<WebSendCount)
		{
			SBUF = ZigbeeUartSend[WebSendPos];
			WebSendPos++;			
			while(!TI);    //若TI=0，在此等待  
			TI = 0; 
		}
	}	
}

void SOURCEvoiceTime(unsigned char hour,unsigned char minute )
{
	if(hour<10 && hour>0)	//小于十时
	{
		if(minute<10)
		{
			ZigbeeUartSend[0] = 0XAA;
			ZigbeeUartSend[1] = 0X1B;
			ZigbeeUartSend[2] = 0X06;		//长度
			ZigbeeUartSend[3] = 0X32;
			ZigbeeUartSend[4] = 0X33;		//第一段  ‘当前时间’
			ZigbeeUartSend[5] = 0X30;
			ZigbeeUartSend[6] = hour%10+0X30;	//温度值
			ZigbeeUartSend[7] = 0X32;
			ZigbeeUartSend[8] = 0X34;       //第三段  ‘小时’
			ZigbeeUartSend[9] = 0X30;
			ZigbeeUartSend[10] = minute%10+0X30;	//温度值
			ZigbeeUartSend[11] = 0X32;
			ZigbeeUartSend[12] = 0X35;       //第三段  ‘小时’
			ZigbeeUartSend[13] = (ZigbeeUartSend[0]
								+ZigbeeUartSend[1]
								+ZigbeeUartSend[2]
								+ZigbeeUartSend[3]
								+ZigbeeUartSend[4]
								+ZigbeeUartSend[5]
								+ZigbeeUartSend[6]
								+ZigbeeUartSend[7]
								+ZigbeeUartSend[8]
								+ZigbeeUartSend[9]
								+ZigbeeUartSend[10]
								+ZigbeeUartSend[11]
								+ZigbeeUartSend[12])/256;		
			WebSendCount = 14; 
			WebSendPos=1;	
			while(WebSendPos<WebSendCount)
			{
				SBUF = ZigbeeUartSend[WebSendPos];
				WebSendPos++;			
				while(!TI);    //若TI=0，在此等待  
				TI = 0; 
			}
		}
		else if(minute == 10)
		{
			ZigbeeUartSend[0] = 0XAA;
			ZigbeeUartSend[1] = 0X1B;
			ZigbeeUartSend[2] = 0X06;		//长度
			ZigbeeUartSend[3] = 0X32;
			ZigbeeUartSend[4] = 0X33;		//第一段  ‘当前时间’
			ZigbeeUartSend[5] = 0X30;
			ZigbeeUartSend[6] = hour%10+0X30;	//小时数
			ZigbeeUartSend[7] = 0X32;
			ZigbeeUartSend[8] = 0X34;       //第三段  ‘小时’
			ZigbeeUartSend[9] = 0X31;
			ZigbeeUartSend[10] = 0X30;		//分钟数
			ZigbeeUartSend[11] = 0X32;
			ZigbeeUartSend[12] = 0X35;       //第三段  ‘分钟’
			
			ZigbeeUartSend[13] = (ZigbeeUartSend[0]
								+ZigbeeUartSend[1]
								+ZigbeeUartSend[2]
								+ZigbeeUartSend[3]
								+ZigbeeUartSend[4]
								+ZigbeeUartSend[5]
								+ZigbeeUartSend[6]
								+ZigbeeUartSend[7]
								+ZigbeeUartSend[8]
								+ZigbeeUartSend[9]
								+ZigbeeUartSend[10]
								+ZigbeeUartSend[11]
								+ZigbeeUartSend[12])/256;		
			WebSendCount = 14; 
			WebSendPos=1;	
			while(WebSendPos<WebSendCount)
			{
				SBUF = ZigbeeUartSend[WebSendPos];
				WebSendPos++;			
				while(!TI);    //若TI=0，在此等待  
				TI = 0; 
			}
		}
		else
		{
			ZigbeeUartSend[0] = 0XAA;
			ZigbeeUartSend[1] = 0X1B;
			ZigbeeUartSend[2] = 0X06;		//长度
			ZigbeeUartSend[3] = 0X32;
			ZigbeeUartSend[4] = 0X33;		//第一段  ‘当前时间’
			ZigbeeUartSend[5] = 0X30;
			ZigbeeUartSend[6] = hour%10+0X30;	//小时数
			ZigbeeUartSend[7] = 0X32;
			ZigbeeUartSend[8] = 0X34;       //第三段  ‘小时’
			ZigbeeUartSend[8] = 0x30;
			ZigbeeUartSend[9] = minute/10+0X30;
			ZigbeeUartSend[10] = 0x31;
			ZigbeeUartSend[11] = 0x30;
			ZigbeeUartSend[12] = 0X30;		//分钟数
			ZigbeeUartSend[13] = minute%10 + 0x30;
			ZigbeeUartSend[14] = 0X32;
			ZigbeeUartSend[15] = 0X35;       //第三段  ‘分钟’
			
			ZigbeeUartSend[16] = (ZigbeeUartSend[0]
								+ZigbeeUartSend[1]
								+ZigbeeUartSend[2]
								+ZigbeeUartSend[3]
								+ZigbeeUartSend[4]
								+ZigbeeUartSend[5]
								+ZigbeeUartSend[6]
								+ZigbeeUartSend[7]
								+ZigbeeUartSend[8]
								+ZigbeeUartSend[9]
								+ZigbeeUartSend[10]
								+ZigbeeUartSend[11]
								+ZigbeeUartSend[12]
								+ZigbeeUartSend[13]
								+ZigbeeUartSend[14]
								+ZigbeeUartSend[15])/256;		
			WebSendCount = 17; 
			WebSendPos=1;	
			while(WebSendPos<WebSendCount)
			{
				SBUF = ZigbeeUartSend[WebSendPos];
				WebSendPos++;			
				while(!TI);    //若TI=0，在此等待  
				TI = 0; 
			}
		}
	}
	else if(hour==10)	//等于十时
	{
		if(minute<10)
		{
			ZigbeeUartSend[0] = 0XAA;
			ZigbeeUartSend[1] = 0X1B;
			ZigbeeUartSend[2] = 0X06;		//长度
			ZigbeeUartSend[3] = 0X32;
			ZigbeeUartSend[4] = 0X33;		//第一段  ‘当前时间’
			ZigbeeUartSend[5] = 0X31;
			ZigbeeUartSend[6] = 0X30;		//时
			ZigbeeUartSend[7] = 0X32;
			ZigbeeUartSend[8] = 0X34;       //第三段  ‘时’
			ZigbeeUartSend[9] = 0X30;
			ZigbeeUartSend[10] = minute%10+0X30;	//分钟数
			ZigbeeUartSend[11] = 0X32;
			ZigbeeUartSend[12] = 0X35;       //第三段  ‘分钟’
			
			ZigbeeUartSend[13] = (ZigbeeUartSend[0]
								+ZigbeeUartSend[1]
								+ZigbeeUartSend[2]
								+ZigbeeUartSend[3]
								+ZigbeeUartSend[4]
								+ZigbeeUartSend[5]
								+ZigbeeUartSend[6]
								+ZigbeeUartSend[7]
								+ZigbeeUartSend[8]
								+ZigbeeUartSend[9]
								+ZigbeeUartSend[10]
								+ZigbeeUartSend[11]
								+ZigbeeUartSend[12])/256;		
			WebSendCount = 14; 
			WebSendPos=1;	
			while(WebSendPos<WebSendCount)
			{
				SBUF =  ZigbeeUartSend[WebSendPos];
				WebSendPos++;
			}
		}
		else if(minute == 10)
		{
			ZigbeeUartSend[0] = 0XAA;
			ZigbeeUartSend[1] = 0X1B;
			ZigbeeUartSend[2] = 0X06;		//长度
			ZigbeeUartSend[3] = 0X32;
			ZigbeeUartSend[4] = 0X33;		//第一段  ‘当前时间’
			ZigbeeUartSend[5] = 0X31;
			ZigbeeUartSend[6] = 0X30;	//小时数
			ZigbeeUartSend[7] = 0X32;
			ZigbeeUartSend[8] = 0X34;       //第三段  ‘小时’
			ZigbeeUartSend[9] = 0X31;
			ZigbeeUartSend[10] = 0X30;		//分钟数
			ZigbeeUartSend[11] = 0X32;
			ZigbeeUartSend[12] = 0X35;       //第三段  ‘分钟’
			
			ZigbeeUartSend[13] = (ZigbeeUartSend[0]
								+ZigbeeUartSend[1]
								+ZigbeeUartSend[2]
								+ZigbeeUartSend[3]
								+ZigbeeUartSend[4]
								+ZigbeeUartSend[5]
								+ZigbeeUartSend[6]
								+ZigbeeUartSend[7]
								+ZigbeeUartSend[8]
								+ZigbeeUartSend[9]
								+ZigbeeUartSend[10]
								+ZigbeeUartSend[11]
								+ZigbeeUartSend[12])/256;		
			WebSendCount = 14; 
			WebSendPos=1;	
			while(WebSendPos<WebSendCount)
			{
				SBUF =  ZigbeeUartSend[WebSendPos];
				WebSendPos++;
			}
		}
		else
		{
			ZigbeeUartSend[0] = 0XAA;
			ZigbeeUartSend[1] = 0X1B;
			ZigbeeUartSend[2] = 0X06;		//长度
			ZigbeeUartSend[3] = 0X32;
			ZigbeeUartSend[4] = 0X33;		//第一段  ‘当前时间’
			ZigbeeUartSend[5] = 0X31;
			ZigbeeUartSend[6] = 0X30;	//小时数
			ZigbeeUartSend[7] = 0X32;
			ZigbeeUartSend[8] = 0X34;       //第三段  ‘小时’
			ZigbeeUartSend[8] = 0x30;
			ZigbeeUartSend[9] = minute/10+0X30;
			ZigbeeUartSend[10] = 0x31;
			ZigbeeUartSend[11] = 0x30;
			ZigbeeUartSend[12] = 0X30;		//分钟数
			ZigbeeUartSend[13] = minute%10 + 0x30;
			ZigbeeUartSend[14] = 0X32;
			ZigbeeUartSend[15] = 0X35;       //第三段  ‘分钟’
			
			ZigbeeUartSend[16] = (ZigbeeUartSend[0]
								+ZigbeeUartSend[1]
								+ZigbeeUartSend[2]
								+ZigbeeUartSend[3]
								+ZigbeeUartSend[4]
								+ZigbeeUartSend[5]
								+ZigbeeUartSend[6]
								+ZigbeeUartSend[7]
								+ZigbeeUartSend[8]
								+ZigbeeUartSend[9]
								+ZigbeeUartSend[10]
								+ZigbeeUartSend[11]
								+ZigbeeUartSend[12]
								+ZigbeeUartSend[13]
								+ZigbeeUartSend[14]
								+ZigbeeUartSend[15])/256;		
			WebSendCount = 17; 
			WebSendPos=1;	
			while(WebSendPos<WebSendCount)
			{
				SBUF =  ZigbeeUartSend[WebSendPos];
				WebSendPos++;
			}
		
		}
	}
	else	//大于十小时
	{
		if(minute<10)
		{
			ZigbeeUartSend[0] = 0XAA;
			ZigbeeUartSend[1] = 0X1B;
			ZigbeeUartSend[2] = 0X06;		//长度
			ZigbeeUartSend[3] = 0X32;
			ZigbeeUartSend[4] = 0X33;		//第一段  ‘当前时间’
			ZigbeeUartSend[5] = 0X30;
			ZigbeeUartSend[6] = hour/10+0X30;	//温度值
			ZigbeeUartSend[7] = 0X31;
			ZigbeeUartSend[8] = 0X30;			//十
			ZigbeeUartSend[9] = 0X30;
			ZigbeeUartSend[10] = hour%10+0X30;	//温度值
			ZigbeeUartSend[11] = 0X32;
			ZigbeeUartSend[12] = 0X34;       //第三段  ‘小时’
			ZigbeeUartSend[13] = 0X30;
			ZigbeeUartSend[14] = minute%10+0X30;	//温度值
			ZigbeeUartSend[15] = 0X32;
			ZigbeeUartSend[16] = 0X35;       //第三段  ‘小时’
			
			ZigbeeUartSend[17] = (ZigbeeUartSend[0]
								+ZigbeeUartSend[1]
								+ZigbeeUartSend[2]
								+ZigbeeUartSend[3]
								+ZigbeeUartSend[4]
								+ZigbeeUartSend[5]
								+ZigbeeUartSend[6]
								+ZigbeeUartSend[7]
								+ZigbeeUartSend[8]
								+ZigbeeUartSend[9]
								+ZigbeeUartSend[10]
								+ZigbeeUartSend[11]
								+ZigbeeUartSend[12]
								+ZigbeeUartSend[13]
								+ZigbeeUartSend[14]
								+ZigbeeUartSend[15]
								+ZigbeeUartSend[16])/256;		
			WebSendCount = 18; 
			WebSendPos=1;	
			while(WebSendPos<WebSendCount)
			{
				SBUF =  ZigbeeUartSend[WebSendPos];
				WebSendPos++;
			}
		}
		else if(minute == 10)
		{
			ZigbeeUartSend[0] = 0XAA;
			ZigbeeUartSend[1] = 0X1B;
			ZigbeeUartSend[2] = 0X06;		//长度
			ZigbeeUartSend[3] = 0X32;
			ZigbeeUartSend[4] = 0X33;		//第一段  ‘当前时间’
			ZigbeeUartSend[5] = 0X30;
			ZigbeeUartSend[6] = hour/10+0X30;	//温度值
			ZigbeeUartSend[7] = 0X31;
			ZigbeeUartSend[8] = 0X30;			//十
			ZigbeeUartSend[9] = 0X30;
			ZigbeeUartSend[10] = hour%10+0X30;	//温度值
			ZigbeeUartSend[11] = 0X32;
			ZigbeeUartSend[12] = 0X34;       //第三段  ‘小时’
			ZigbeeUartSend[13] = 0X31;
			ZigbeeUartSend[14] = 0X30;	//温度值
			ZigbeeUartSend[15] = 0X32;
			ZigbeeUartSend[16] = 0X35;       //第三段  ‘小时’
			
			ZigbeeUartSend[17] = (ZigbeeUartSend[0]
								+ZigbeeUartSend[1]
								+ZigbeeUartSend[2]
								+ZigbeeUartSend[3]
								+ZigbeeUartSend[4]
								+ZigbeeUartSend[5]
								+ZigbeeUartSend[6]
								+ZigbeeUartSend[7]
								+ZigbeeUartSend[8]
								+ZigbeeUartSend[9]
								+ZigbeeUartSend[10]
								+ZigbeeUartSend[11]
								+ZigbeeUartSend[12]
								+ZigbeeUartSend[13]
								+ZigbeeUartSend[14]
								+ZigbeeUartSend[15]
								+ZigbeeUartSend[16])/256;		
			WebSendCount = 18; 
			WebSendPos=1;	
			while(WebSendPos<WebSendCount)
			{
				SBUF =  ZigbeeUartSend[WebSendPos];
				WebSendPos++;
			}
		}
		else
		{
			ZigbeeUartSend[0] = 0XAA;
			ZigbeeUartSend[1] = 0X1B;
			ZigbeeUartSend[2] = 0X06;		//长度
			ZigbeeUartSend[3] = 0X32;
			ZigbeeUartSend[4] = 0X33;		//第一段  ‘当前时间’
			ZigbeeUartSend[5] = 0X30;
			ZigbeeUartSend[6] = hour/10+0X30;	//温度值
			ZigbeeUartSend[7] = 0X31;
			ZigbeeUartSend[8] = 0X30;			//十
			ZigbeeUartSend[9] = 0X30;
			ZigbeeUartSend[10] = hour%10+0X30;	//温度值
			ZigbeeUartSend[11] = 0X32;
			ZigbeeUartSend[12] = 0X34;       //第三段  ‘小时’
			ZigbeeUartSend[13] = 0X30;
			ZigbeeUartSend[14] = minute/10+0X30;	//分钟
			ZigbeeUartSend[15] = 0X31;
			ZigbeeUartSend[16] = 0X30;	//分钟
			ZigbeeUartSend[17] = 0X30;
			ZigbeeUartSend[18] = minute%10+0X30;	//分钟
			ZigbeeUartSend[19] = 0X32;
			ZigbeeUartSend[20] = 0X35;       //第三段  ‘小时
			
			ZigbeeUartSend[21] = (ZigbeeUartSend[0]
								+ZigbeeUartSend[1]
								+ZigbeeUartSend[2]
								+ZigbeeUartSend[3]
								+ZigbeeUartSend[4]
								+ZigbeeUartSend[5]
								+ZigbeeUartSend[6]
								+ZigbeeUartSend[7]
								+ZigbeeUartSend[8]
								+ZigbeeUartSend[9]
								+ZigbeeUartSend[10]
								+ZigbeeUartSend[11]
								+ZigbeeUartSend[12]
								+ZigbeeUartSend[13]
								+ZigbeeUartSend[14]
								+ZigbeeUartSend[15]
								+ZigbeeUartSend[16]
								+ZigbeeUartSend[17]
								+ZigbeeUartSend[18]
								+ZigbeeUartSend[19]
								+ZigbeeUartSend[20])/256;		
			WebSendCount = 22; 
			WebSendPos=1;	
			while(WebSendPos<WebSendCount)
			{
				SBUF =  ZigbeeUartSend[WebSendPos];
				WebSendPos++;
			}
		
		}
	}
}

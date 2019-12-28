#include "XY-V17B.h"
#include "uart.h"



unsigned char  WebSendCount = 1;
unsigned char  WebSendPos   = 0;
unsigned char  ZigbeeUartSend[15];
unsigned char  ZigbeeUartSend_oled[10];
unsigned char  TF_Mode[]       = {0xaa, 0x0B, 0x01, 0x01, 0xB7, 0XFF };
unsigned char  COMD_Play[]     = {0xAA, 0x1B, 0x00, 0XAC, 0XFF       };
unsigned char  COMD_Stop[]     = {0xaa, 0x04, 0x00, 0xae, 0XFF       };	//
unsigned char  COMD_panfu[]    = {0xaa, 0x09, 0x00, 0xB3, 0XFF       };   //�̷���ѯ
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
	SCON=0x50;	    //����ѡ��ģʽ1, 8-bit UART, ʹ�ܽ���    
    TMOD|=0x20;     //�ö�ʱ��1���ò�����
    TH1=0xFD;     
    TR1=1;           
	TI=1; 			//���������ж�
	ES = 1;
	EA = 1;
}
//���������¶�
void SOURCEvoice_Tempriture(unsigned char TEMPTURE )
{
	if(TEMPTURE>0 && TEMPTURE<10)	//С��10��
	{
		
		ZigbeeUartSend[0] = 0xAA;
		ZigbeeUartSend[1] = 0x1B;
		ZigbeeUartSend[2] = 0x06;		//����
		ZigbeeUartSend[3] = 0x32;
		ZigbeeUartSend[4] = 0x31;		//��һ��  ����ǰ���롯
		ZigbeeUartSend[5] = 0x30;
		ZigbeeUartSend[6] = TEMPTURE+0x30;	//����ֵ
		ZigbeeUartSend[7] = 0x32;
		ZigbeeUartSend[8] = 0x32;       //������  �����ס�
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
	}
	else if(TEMPTURE>=10 &&TEMPTURE<20)	//ʮ����ʮ��
	{
		ZigbeeUartSend[0] = 0xAA;
		ZigbeeUartSend[1] = 0x1B;
		ZigbeeUartSend[2] = 0x06;		//����
		ZigbeeUartSend[3] = 0x32;
		ZigbeeUartSend[4] = 0x31;		//��ǰ�¶�
		ZigbeeUartSend[5] = 0x31;
		ZigbeeUartSend[6] = TEMPTURE%10+0x30;  //�¶�ֵ
		ZigbeeUartSend[7] = 0x32;
		ZigbeeUartSend[8] = 0x32;       //������  �����϶ȡ�
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
	}
	else 
	{
		ZigbeeUartSend[0]  = 0xAA;
		ZigbeeUartSend[1]  = 0x1B;
		ZigbeeUartSend[2]  = 0x08;  //����
		ZigbeeUartSend[3]  = 0x32;
		ZigbeeUartSend[4]  = 0x31;		//��ǰ�¶�
		ZigbeeUartSend[5]  = 0x30;
		ZigbeeUartSend[6]  = TEMPTURE/10+0x30;	//�¶�ֵ
		ZigbeeUartSend[7]  = 0x31;
		ZigbeeUartSend[8]  = TEMPTURE%10 +0x30;
		ZigbeeUartSend[9]  = 0x32;
		ZigbeeUartSend[10] = 0x32;       //������  �����϶�	
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
	}	
	while(WebSendPos<WebSendCount)
	{
		SBUF = ZigbeeUartSend[WebSendPos];
		WebSendPos++;			
		while(!TI);    //��TI=0���ڴ˵ȴ�  
		TI = 0; 
	}
}

//������������
void SOURCEvoice_Distance(unsigned char TEMPDIS )
{
	if(TEMPDIS<10 && TEMPDIS>0)	//С��10��
	{
		ZigbeeUartSend[0] = 0XAA;
		ZigbeeUartSend[1] = 0X1B;
		ZigbeeUartSend[2] = 0X06;		//����
		ZigbeeUartSend[3] = 0X32;
		ZigbeeUartSend[4] = 0X36;		//��һ��  ����ǰ���롯
		ZigbeeUartSend[5] = 0X30;
		ZigbeeUartSend[6] = TEMPDIS+0X30;	//����ֵ
		ZigbeeUartSend[7] = 0x32;
		ZigbeeUartSend[8] = 0X37;       //������  �����ס�
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
	}
	else if(TEMPDIS == 10)     //10�ֿ�����
	{
		ZigbeeUartSend[0] = 0XAA;
		ZigbeeUartSend[1] = 0X1B;
		ZigbeeUartSend[2] = 0X06;		//����
		ZigbeeUartSend[3] = 0X32;
		ZigbeeUartSend[4] = 0X36;		//��һ��  ����ǰ�¶ȡ�
		ZigbeeUartSend[5] = 0X31;		
		ZigbeeUartSend[6] = 0X30;       //�ڶ���  �¶�
		ZigbeeUartSend[7] = 0X32;
		ZigbeeUartSend[8] = 0X37;       //������  �����϶�
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
	}
	else if(TEMPDIS>=10 &&TEMPDIS<20)	//ʮ����ʮ��
	{
		ZigbeeUartSend[0] = 0XAA;
		ZigbeeUartSend[1] = 0X1B;
		ZigbeeUartSend[2] = 0X06;		//����
		ZigbeeUartSend[3] = 0X32;
		ZigbeeUartSend[4] = 0X36;		//��ǰ�¶�
		ZigbeeUartSend[5] = 0X31;
		ZigbeeUartSend[6] = TEMPDIS%10+0x30;  //�¶�ֵ
		ZigbeeUartSend[7] = 0X32;
		ZigbeeUartSend[8] = 0X37;       //������  �����϶ȡ�
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
	}
	else if(TEMPDIS>100)		//������������1��
	{
		ZigbeeUartSend[0] = 0XAA;
		ZigbeeUartSend[1] = 0X1B;
		ZigbeeUartSend[2] = 0X02;		//����
		ZigbeeUartSend[3] = 0X32;
		ZigbeeUartSend[4] = 0x38;  //����ֵ
		ZigbeeUartSend[5] = (ZigbeeUartSend[0]
							+ZigbeeUartSend[1]
							+ZigbeeUartSend[2]
							+ZigbeeUartSend[3]
							+ZigbeeUartSend[4])%256;
		WebSendCount = 6; 
		WebSendPos=0;
	}
	else 
	{
		ZigbeeUartSend[0]  = 0XAA;
		ZigbeeUartSend[1]  = 0X1B;
		ZigbeeUartSend[2]  = 0X08;  //����
		ZigbeeUartSend[3]  = 0X32;
		ZigbeeUartSend[4]  = 0X36;		//��ǰ����
		ZigbeeUartSend[5]  = 0X30;
		ZigbeeUartSend[6]  = TEMPDIS/10+0x30;	//����ֵ
		ZigbeeUartSend[7]  = 0X31;
		ZigbeeUartSend[8]  = TEMPDIS%10 +0x30;
		ZigbeeUartSend[9]  = 0X32;
		ZigbeeUartSend[10] = 0X37;       //������  �����ס�	
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
	}	
	while(WebSendPos<WebSendCount)
	{
		SBUF = ZigbeeUartSend[WebSendPos];
		WebSendPos++;			
		while(!TI);    //��TI=0���ڴ˵ȴ�  
		TI = 0; 
	}
}
//��������ʱ��
void SOURCEvoiceTime(unsigned char hour,unsigned char  minute )
{
	if(hour<10 && hour>0)	//С��ʮʱ
	{
		if(minute<10)
		{
			ZigbeeUartSend[0] = 0xAA;
			ZigbeeUartSend[1] = 0x1B;
			ZigbeeUartSend[2] = 0x0A;		//����
			
			ZigbeeUartSend[3] = 0x32;
			ZigbeeUartSend[4] = 0x33;		//��һ��  ����ǰʱ�䡯
			
			ZigbeeUartSend[5] = 0x30;
			ZigbeeUartSend[6] = hour+0x30;	//Сʱ
			
			ZigbeeUartSend[7] = 0x32;
			ZigbeeUartSend[8] = 0x34;       //������  ��Сʱ��
			
			ZigbeeUartSend[9] = 0x30;
			ZigbeeUartSend[10] = minute+0x30;	//����
			
			ZigbeeUartSend[11] = 0x32;
			ZigbeeUartSend[12] = 0x35;       //������  �����ӡ�
			
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
								 +ZigbeeUartSend[12])%256;		
			WebSendCount = 14; 
			WebSendPos=0;	
		}
		else if(minute >= 10 && minute<20)
		{
			ZigbeeUartSend[0]  = 0xAA;
			ZigbeeUartSend[1]  = 0x1B;
			ZigbeeUartSend[2]  = 0x0A;		//����
			
			ZigbeeUartSend[3]  = 0x32;
			ZigbeeUartSend[4]  = 0x33;		//��һ��  ����ǰʱ�䡯
			
			ZigbeeUartSend[5]  = 0x30;
			ZigbeeUartSend[6]  = 0x30 + hour;	//Сʱ��
			
			ZigbeeUartSend[7]  = 0x32;
			ZigbeeUartSend[8]  = 0x34;       //������  ��Сʱ��
			
			ZigbeeUartSend[9]  = 0x31;
			ZigbeeUartSend[10] = 0x30 + minute%10;		//������
			
			ZigbeeUartSend[11] = 0x32;
			ZigbeeUartSend[12] = 0x35;       //������  �����ӡ�
			
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
								+ZigbeeUartSend[12])%256;		
			WebSendCount = 14; 
			WebSendPos=0;	
		}
		else
		{
			ZigbeeUartSend[0]  = 0xAA;
			ZigbeeUartSend[1]  = 0x1B;
			ZigbeeUartSend[2]  = 0x0C;		//����
			
			ZigbeeUartSend[3]  = 0x32;
			ZigbeeUartSend[4]  = 0x33;		//��һ��  ����ǰʱ�䡯
			
			ZigbeeUartSend[5]  = 0x30;
			ZigbeeUartSend[6]  = hour+0x30;	//Сʱ��
			
			ZigbeeUartSend[7]  = 0x32;
			ZigbeeUartSend[8]  = 0x34;       //������  ��Сʱ��
			
			ZigbeeUartSend[9]  = 0x30;
			ZigbeeUartSend[10]  = minute/10+0x30;
			ZigbeeUartSend[11] = 0x31;
			ZigbeeUartSend[12] = minute%10 + 0x30;
			
			ZigbeeUartSend[13] = 0x32;
			ZigbeeUartSend[14] = 0x35;       //������  �����ӡ�
			
			ZigbeeUartSend[15] = (ZigbeeUartSend[0]
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
								+ZigbeeUartSend[14])%256;		
			WebSendCount = 16; 
			WebSendPos=0;	
		}
	}
	else if(hour >= 10  && hour <20) 	//����ʮʱ
	{
		if(minute<10)
		{
			ZigbeeUartSend[0] = 0xAA;
			ZigbeeUartSend[1] = 0x1B;
			ZigbeeUartSend[2] = 0x0A;		//����
			
			ZigbeeUartSend[3] = 0x32;
			ZigbeeUartSend[4] = 0x33;		//��һ��  ����ǰʱ�䡯
			
			ZigbeeUartSend[5] = 0x31;
			ZigbeeUartSend[6] = hour%10+0x30;	//Сʱ
			
			ZigbeeUartSend[7] = 0x32;
			ZigbeeUartSend[8] = 0x34;       //������  ��Сʱ��
			
			ZigbeeUartSend[9] = 0x30;
			ZigbeeUartSend[10] = minute+0x30;	//����
			
			ZigbeeUartSend[11] = 0x32;
			ZigbeeUartSend[12] = 0x35;       //������  �����ӡ�
			
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
								 +ZigbeeUartSend[12])%256;		
			WebSendCount = 14; 
			WebSendPos=0;	
		}
		else if(minute >= 10 && minute<20)
		{
			ZigbeeUartSend[0]  = 0xAA;
			ZigbeeUartSend[1]  = 0x1B;
			ZigbeeUartSend[2]  = 0x0A;		//����
			
			ZigbeeUartSend[3]  = 0x32;
			ZigbeeUartSend[4]  = 0x33;		//��һ��  ����ǰʱ�䡯
			
			ZigbeeUartSend[5]  = 0x31;
			ZigbeeUartSend[6]  = hour%10 + 0x30;	//Сʱ��
			
			ZigbeeUartSend[7]  = 0x32;
			ZigbeeUartSend[8]  = 0x34;       //������  ��Сʱ��
			
			ZigbeeUartSend[9]  = 0x31;
			ZigbeeUartSend[10] = minute%10 + 0x30;		//������
			
			ZigbeeUartSend[11] = 0x32;
			ZigbeeUartSend[12] = 0x35;       //������  �����ӡ�
			
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
								+ZigbeeUartSend[12])%256;		
			WebSendCount = 14; 
			WebSendPos=0;	
		}
		else
		{
			ZigbeeUartSend[0]  = 0xAA;
			ZigbeeUartSend[1]  = 0x1B;
			ZigbeeUartSend[2]  = 0x0C;		//����
			
			ZigbeeUartSend[3]  = 0x32;
			ZigbeeUartSend[4]  = 0x33;		//��һ��  ����ǰʱ�䡯
			
			ZigbeeUartSend[5]  = 0x31;
			ZigbeeUartSend[6]  = hour%10+0x30;	//Сʱ��
			
			ZigbeeUartSend[7]  = 0x32;
			ZigbeeUartSend[8]  = 0x34;       //������  ��Сʱ��
			
			ZigbeeUartSend[9]  = 0x30;
			ZigbeeUartSend[10]  = minute/10+0x30;
			ZigbeeUartSend[11] = 0x31;
			ZigbeeUartSend[12] = minute%10 + 0x30;
			
			ZigbeeUartSend[13] = 0x32;
			ZigbeeUartSend[14] = 0x35;       //������  �����ӡ�
			
			ZigbeeUartSend[15] = (ZigbeeUartSend[0]
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
								+ZigbeeUartSend[14])%256;		
			WebSendCount = 16; 
			WebSendPos=0;	
		}
	}
	else	//����20Сʱ
	{
		if(minute<10)
		{
			ZigbeeUartSend[0] = 0xAA;
			ZigbeeUartSend[1] = 0x1B;
			ZigbeeUartSend[2] = 0x0C;		//����
			
			ZigbeeUartSend[3]  = 0x32;
			ZigbeeUartSend[4]  = 0x33;		//��һ��  ����ǰʱ�䡯
			
			ZigbeeUartSend[5] = 0x30;
			ZigbeeUartSend[6] = hour /10+0x30;		//��һ��  ����ǰʱ�䡯
			ZigbeeUartSend[7] = 0x31;
			ZigbeeUartSend[8] = hour%10+0x30;	//Сʱ
			
			ZigbeeUartSend[9] = 0x32;
			ZigbeeUartSend[10] = 0x34;       //������  ��Сʱ��
			
			ZigbeeUartSend[11] = 0x30;
			ZigbeeUartSend[12] = minute+0x30;	//����
			
			ZigbeeUartSend[13] = 0x32;
			ZigbeeUartSend[14] = 0x35;       //������  �����ӡ�
			
			ZigbeeUartSend[15] = (ZigbeeUartSend[0]
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
								 +ZigbeeUartSend[14])%256;		
			WebSendCount = 16; 
			WebSendPos=0;	
		}
		else if(minute >= 10 && minute<20)
		{
			ZigbeeUartSend[0]  = 0xAA;
			ZigbeeUartSend[1]  = 0x1B;
			ZigbeeUartSend[2]  = 0x0C;		//����
			
			ZigbeeUartSend[3]  = 0x32;
			ZigbeeUartSend[4]  = 0x33;		//��һ��  ����ǰʱ�䡯
			
			ZigbeeUartSend[5]  = 0x30;
			ZigbeeUartSend[6]  = hour/10 + 0x30;		//��һ��  ����ǰʱ�䡯
			ZigbeeUartSend[7]  = 0x31;
			ZigbeeUartSend[8]  = hour%10+0x30;	//Сʱ��
			
			ZigbeeUartSend[9]  = 0x32;
			ZigbeeUartSend[10]  = 0x34;       //������  ��Сʱ��
			
			ZigbeeUartSend[11]  = 0x31;
			ZigbeeUartSend[12] = minute%10 + 0x30;		//������
			
			ZigbeeUartSend[13] = 0x32;
			ZigbeeUartSend[14] = 0x35;       //������  �����ӡ�
			
			ZigbeeUartSend[15] = (ZigbeeUartSend[0]
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
								+ZigbeeUartSend[14])%256;		
			WebSendCount = 16; 
			WebSendPos=0;	
		}
		else
		{
			ZigbeeUartSend[0]  = 0xAA;
			ZigbeeUartSend[1]  = 0x1B;
			ZigbeeUartSend[2]  = 0x0E;		//����
			
			ZigbeeUartSend[3]  = 0x32;
			ZigbeeUartSend[4]  = 0x33;		//��һ��  ����ǰʱ�䡯
			
			ZigbeeUartSend[5]  = 0x30;
			ZigbeeUartSend[6]  = hour/10 + 0x30;		//��һ��  ����ǰʱ�䡯
			ZigbeeUartSend[7]  = 0x31;
			ZigbeeUartSend[8]  = hour%10+0x30;	//Сʱ��
			
			ZigbeeUartSend[9]  = 0x32;
			ZigbeeUartSend[10]  = 0x34;       //������  ��Сʱ��
			
			ZigbeeUartSend[11]  = 0x30;
			ZigbeeUartSend[12]  = minute/10+0x30;
			ZigbeeUartSend[13] = 0x31;		
			ZigbeeUartSend[14] = minute%10 + 0x30; //������
			
			ZigbeeUartSend[15] = 0x32;
			ZigbeeUartSend[16] = 0x35;       //������  �����ӡ�
			
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
								+ZigbeeUartSend[16])%256;		
			WebSendCount = 18; 
			WebSendPos=0;	
		}
	}
	while(WebSendPos<WebSendCount)
	{
		SBUF = ZigbeeUartSend[WebSendPos];
		WebSendPos++;			
		while(!TI);    //��TI=0���ڴ˵ȴ�  
		TI = 0; 
	}
}

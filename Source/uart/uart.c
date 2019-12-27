#include "uart.h"

#define S2RI 0x01   //����2�����ж������־λ  
#define S2TI 0x02   //����2�����ж������־λ 

#define FOSC 11059200L      //System frequency
#define BAUD 9600           //UART baudrate

void Uart1Init(void) //9600bps
{   
	TMOD=0x21;		   //��T0Ϊ��ʽ1��GATE=1��
	SCON=0x50;
	TH0=0;
	TL0=0; 
	TR0=1;  
	ET0=1;             //����T0�ж�
	TR1=1;			   //������ʱ��
	TI=1;
	EA=1;			   //�������ж�
	TH1=0xFD;
	TL1=0xFD;
	ET1 = 0;		//��ֹ��ʱ��1�ж�
    EA =1;        	//�����ж�
    ES =1;        	//������1�ж�
    S2CON = 0x50;   //����2�����ڷ�ʽ1  10λ�첽�շ� S2REN=1�������
    BRT = 0xFD;     //���������ʷ�������ֵ
    AUXR = 0x10;    //BRTR=1 ���������ʷ�������ʼ����
    IE2 =0x01;      //������2�ж�  ES2=1
}
/*----------------------------
UART1 ���ʹ�������
-----------------------------*/
void UART1_SendData(unsigned char c)
{
	SBUF = c;  
	while(!TI);    //��TI=0���ڴ˵ȴ�  
	TI = 0;    
}


/*----------------------------
UART1 �����ַ���
-----------------------------*/
void UART1_SendString(unsigned char *s)
{
	while(*s !='\0')//����ַ���������
	{
		UART1_SendData(*s++);//���͵�ǰ�ַ�
	}
}

/*----------------------------
UART2 ���ʹ�������
-----------------------------*/
void UART2_SendData(u8 c)
{
	S2BUF = c;  
	while(!(S2CON&S2TI));  //��S2TI=0���ڴ˵ȴ�  
	S2CON&=~S2TI;     //S2TI=0    
}


/*----------------------------
UART1 �����ַ���
-----------------------------*/
void UART2_SendString(char *s)
{
	while(*s !='\0')//����ַ���������
	{
		UART2_SendData(*s++);//���͵�ǰ�ַ�
	}
}




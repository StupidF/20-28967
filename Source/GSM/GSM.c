#include "GSM.h"
#include "string.h"
#include "uart.h"
#include "delay.h"


 u8 Uart2_Buf[Buf1_Max];

u8 times_r[25];

u8 Times=0,First_Int = 0;
unsigned int   Timer0_start=0;


static unsigned char *SMS_Num="\"+8613800250500\"";//�������ĺ� �������ĺŵĽ��ܿ��Կ����ڵ��Աʼǵĵڶ�����
static unsigned char *phone="\"15655366706\"";     //���Ž��շ��ֻ���
unsigned char content[] = "Please Help mi!"; //���Ͷ�������

/*******************************************************************************
* ������ : CLR_Buf1
* ����   : �������2��������
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void CLR_Buf1(void)
{
	u16 k;
	for(k=0;k<Buf1_Max;k++)      //��������������
	{
		Uart2_Buf[k] = 0x00;
	}
    First_Int = 0;              //�����ַ�������ʼ�洢λ��
}

/*******************************************************************************
* ������ : Find
* ����   : �жϻ������Ƿ���ָ�����ַ���
* ����   : 
* ���   : 
* ����   : unsigned char:1 �ҵ�ָ���ַ���0 δ�ҵ�ָ���ַ� 
* ע��   : 
*******************************************************************************/

u8 Find(u8 *a)
{ 
	if(strstr(Uart2_Buf,a)!=NULL)
	    return 1;
	else
		return 0;
}

/*******************************************************************************
* ������ : Second_AT_Command
* ����   : ����ATָ���
* ����   : �������ݵ�ָ�롢ϣ���յ���Ӧ�𡢷��͵ȴ�ʱ��(��λ��S)
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/

void Second_AT_Command(u8 *b,u8 *a,u8 wait_time)         
{
	u8 i;
	u8 *c;
	c = b;										//�����ַ�����ַ��c
	CLR_Buf1(); 
	i = 0;
	Timer0_start=0;
	while(i == 0)                    
	{
		if(!Find(a))           //������ҪӦ����ַ�
		{
			Timer0_start++;
			if(Timer0_start >(wait_time*300) )//��ʱ���·�������
			{
				Timer0_start= 0;
				b = c;						 //���ַ�����ַ��b
				for (b; *b!='\0';b++)
				{
					UART2_SendData(*b);	
				}
				UART2_SendLR();		//�س�����
		   }
		}
		else
		{
			i = 1;
			Timer0_start = 0;  
		}
	}
	CLR_Buf1(); 
}

/*******************************************************************************
* ������ : Set_Text_Mode
* ����   : ���ö���ΪTEXT�ı�ģʽ
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void Set_Text_Mode(void)
{
	unsigned char temp[50]="AT+CSCA=";
	Second_AT_Command("ATE0","OK",3);							//ȡ������	
	Second_AT_Command("AT+CMGF=1","OK",3);						//TEXTģʽ	
	//Second_AT_Command("AT+CPMS=\"SM\",\"SM\",\"SM\"","OK",3);	//���в�������SIM���н���
	strcat(temp,SMS_Num); 		  //��Ϣ���ĺ����ַ������								//�ַ���ƴ�Ӻ������⺯����
	Second_AT_Command(temp,"OK",3);	//����							//���ö������ĺ�
}
/*******************************************************************************
* ������ : Send_Text_Sms
* ����   : ����TEXT�ı�����
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void Send_Text_Sms(void)
{
	unsigned char temp[50]="AT+CMGS=";
	
	strcat(temp,phone); 			//�ַ���ƴ�Ӻ������⺯����
	Second_AT_Command(temp,">",3); 	//�ȴ����յ���>���ŷ��Ͷ�������
	UART2_SendString(content);     	//���Ͷ�������
	UART2_SendData(0X1A);          	//���ͽ�����
}

/*******************************************************************************
* ������ : Wait_CREG
* ����   : �ȴ�ģ��ע��ɹ�
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void Wait_CREG(void)
{
	u8 i;
	u8 k;
	i = 0;
	CLR_Buf1();
	while(i == 0)        			
	{
		CLR_Buf1();        
		UART2_SendString("AT+CREG?");//��ѯģ������ע��״̬
		UART2_SendLR();       //���ͻس�����
		delay_ms(550);  						
	    for(k=0;k<Buf1_Max;k++)      			
    	{
			if(Uart2_Buf[k] == ':')
			{
				if((Uart2_Buf[k+4] == '1')||(Uart2_Buf[k+4] == '5')) //��������ע��ɹ�
				{
					i = 1;
					break;
				}
			}
		}
	}
}

void Send_SeekhelpMSG()
{
	Set_Text_Mode();	//���ö���ΪTEXTģʽ
	Send_Text_Sms();	//����һ������Ϣ
}

void SendCMD_TIME()
{
	UART2_SendString("AT+CCLK?\r\n");
}

u8 GET_time()
{
	uchar i,j;
	uchar bigin[6]= "+CCLK:";
	uchar *resault;
	for(i=0;i<Buf1_Max;i++)
	{
		if((Uart2_Buf[i]=='"') && (Uart2_Buf[i-1]==' ')||(Uart2_Buf[i]=='"') && (Uart2_Buf[i-1]==':'))
		{
			for(j=0;j<25;j++)
			{
				times_r[j]=0;
			}
			for(j=0;j<25;j++)
			{
				times_r[j]= Uart2_Buf[i+j];
			}	
			times_r[j] = '\0';
//			UART1_SendString(times_r);
			return;
		}
	}
}
	
	
void GSM_INIT(void)
{
	UART2_SendString("AT+CLTS=1\r\n");
	Wait_CREG();		//�ȴ�ģ������ע��ɹ�
}

/*******************************************************************************
* ������ : Uart2 
* ����   : ����2�жϷ�����ں���
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
void Uart2() interrupt 8
{
    if ( S2CON&S2RI)
    {
		S2CON&=~S2RI;                 	 //���RIλ
		Uart2_Buf[First_Int] = S2BUF;  	 //�����յ����ַ����浽������
		//UART1_SendData(Uart2_Buf[First_Int]);
		First_Int++;                	 //����ָ������ƶ�
		if(First_Int > Buf1_Max)       	 //���������,������ָ��ָ�򻺴���׵�ַ
		{
			First_Int = 0;
		}
    }
}

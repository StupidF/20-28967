#ifndef _GSM_H_
#define _GSM_H_


#include "config.h"


#define S2RI 0x01   //����2�����ж������־λ  
#define S2TI 0x02   //����2�����ж������־λ



/*************  ���ر�������	**************/
#define Buf1_Max 100 			//����1���泤��


void Timer0Init(void);  //��ʱ��0��ʼ��
void CLR_Buf1(void);    //�崮�ڽ��ջ���
u8 Find(u8 *a);         //�����ַ���
void Second_AT_Command(u8 *b,u8 *a,u8 wait_time);  //����ָ��
void Wait_CREG(void);   //��ѯ�ȴ�ģ��ע��ɹ�
void Set_Text_Mode(void); //���ö���ΪTEXTģʽ
void Send_Text_Sms(void); //����һ��TEXT����
void Send_SeekhelpMSG();
void GSM_INIT(void);
void SendCMD_TIME();
u8 GET_time();



#endif

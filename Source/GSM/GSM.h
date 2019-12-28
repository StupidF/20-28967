#ifndef _GSM_H_
#define _GSM_H_


#include "config.h"


#define S2RI 0x01   //串口2接收中断请求标志位  
#define S2TI 0x02   //串口2发送中断请求标志位



/*************  本地变量声明	**************/
#define Buf1_Max 100 			//串口1缓存长度


void Timer0Init(void);  //定时器0初始化
void CLR_Buf1(void);    //清串口接收缓存
u8 Find(u8 *a);         //查找字符串
void Second_AT_Command(u8 *b,u8 *a,u8 wait_time);  //发送指令
void Wait_CREG(void);   //查询等待模块注册成功
void Set_Text_Mode(void); //设置短信为TEXT模式
void Send_Text_Sms(void); //发送一条TEXT短信
void Send_SeekhelpMSG();
void GSM_INIT(void);
void SendCMD_TIME();
u8 GET_time();



#endif

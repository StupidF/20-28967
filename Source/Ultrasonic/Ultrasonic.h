#ifndef _Ultrasonic_h_
#define _Ultrasonic_h_ 

#include "config.h"

sbit  RX = P3^2;
sbit  TX = P3^3;

sbit RUNING_LED = P0^0;			//����ָʾ��
sbit BEEP       = P0^1;			//������
void Ultrasonic_Init();
unsigned int Conut();
//unsigned int GetDIS(void);

#endif 

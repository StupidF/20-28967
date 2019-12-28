#include "GSM.h"
#include "string.h"
#include "uart.h"
#include "delay.h"


 u8 Uart2_Buf[Buf1_Max];

u8 times_r[25];

u8 Times=0,First_Int = 0;
unsigned int   Timer0_start=0;


static unsigned char *SMS_Num="\"+8613800250500\"";//短信中心号 关于中心号的介绍可以看串口调试笔记的第二部分
static unsigned char *phone="\"15655366706\"";     //短信接收方手机号
unsigned char content[] = "Please Help mi!"; //发送短信内容

/*******************************************************************************
* 函数名 : CLR_Buf1
* 描述   : 清除串口2缓存数据
* 输入   : 
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/
void CLR_Buf1(void)
{
	u16 k;
	for(k=0;k<Buf1_Max;k++)      //将缓存内容清零
	{
		Uart2_Buf[k] = 0x00;
	}
    First_Int = 0;              //接收字符串的起始存储位置
}

/*******************************************************************************
* 函数名 : Find
* 描述   : 判断缓存中是否含有指定的字符串
* 输入   : 
* 输出   : 
* 返回   : unsigned char:1 找到指定字符，0 未找到指定字符 
* 注意   : 
*******************************************************************************/

u8 Find(u8 *a)
{ 
	if(strstr(Uart2_Buf,a)!=NULL)
	    return 1;
	else
		return 0;
}

/*******************************************************************************
* 函数名 : Second_AT_Command
* 描述   : 发送AT指令函数
* 输入   : 发送数据的指针、希望收到的应答、发送等待时间(单位：S)
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/

void Second_AT_Command(u8 *b,u8 *a,u8 wait_time)         
{
	u8 i;
	u8 *c;
	c = b;										//保存字符串地址到c
	CLR_Buf1(); 
	i = 0;
	Timer0_start=0;
	while(i == 0)                    
	{
		if(!Find(a))           //查找需要应答的字符
		{
			Timer0_start++;
			if(Timer0_start >(wait_time*300) )//超时重新发送命令
			{
				Timer0_start= 0;
				b = c;						 //将字符串地址给b
				for (b; *b!='\0';b++)
				{
					UART2_SendData(*b);	
				}
				UART2_SendLR();		//回车换行
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
* 函数名 : Set_Text_Mode
* 描述   : 设置短信为TEXT文本模式
* 输入   : 
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/
void Set_Text_Mode(void)
{
	unsigned char temp[50]="AT+CSCA=";
	Second_AT_Command("ATE0","OK",3);							//取消回显	
	Second_AT_Command("AT+CMGF=1","OK",3);						//TEXT模式	
	//Second_AT_Command("AT+CPMS=\"SM\",\"SM\",\"SM\"","OK",3);	//所有操作都在SIM卡中进行
	strcat(temp,SMS_Num); 		  //信息中心号码字符串组合								//字符串拼接函数（库函数）
	Second_AT_Command(temp,"OK",3);	//发送							//设置短信中心号
}
/*******************************************************************************
* 函数名 : Send_Text_Sms
* 描述   : 发送TEXT文本短信
* 输入   : 
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/
void Send_Text_Sms(void)
{
	unsigned char temp[50]="AT+CMGS=";
	
	strcat(temp,phone); 			//字符串拼接函数（库函数）
	Second_AT_Command(temp,">",3); 	//等待接收到“>”才发送短信内容
	UART2_SendString(content);     	//发送短信内容
	UART2_SendData(0X1A);          	//发送结束符
}

/*******************************************************************************
* 函数名 : Wait_CREG
* 描述   : 等待模块注册成功
* 输入   : 
* 输出   : 
* 返回   : 
* 注意   : 
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
		UART2_SendString("AT+CREG?");//查询模块网络注册状态
		UART2_SendLR();       //发送回车换行
		delay_ms(550);  						
	    for(k=0;k<Buf1_Max;k++)      			
    	{
			if(Uart2_Buf[k] == ':')
			{
				if((Uart2_Buf[k+4] == '1')||(Uart2_Buf[k+4] == '5')) //表明网络注册成功
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
	Set_Text_Mode();	//设置短信为TEXT模式
	Send_Text_Sms();	//发送一条短消息
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
	Wait_CREG();		//等待模块网络注册成功
}

/*******************************************************************************
* 函数名 : Uart2 
* 描述   : 串口2中断服务入口函数
* 输入   : 
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/
void Uart2() interrupt 8
{
    if ( S2CON&S2RI)
    {
		S2CON&=~S2RI;                 	 //清除RI位
		Uart2_Buf[First_Int] = S2BUF;  	 //将接收到的字符串存到缓存中
		//UART1_SendData(Uart2_Buf[First_Int]);
		First_Int++;                	 //缓存指针向后移动
		if(First_Int > Buf1_Max)       	 //如果缓存满,将缓存指针指向缓存的首地址
		{
			First_Int = 0;
		}
    }
}

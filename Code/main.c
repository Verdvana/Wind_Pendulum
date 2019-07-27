#include <STC12C5A.H>
#include <INTRINS.h>
#include "stdio.h"
#include "string.h"
#include "usart.h"
#include "timer.h"
#include "PWM.h"
#include "1602.h"
#include "find_road.h"
#include "yundong.h"
#include "CEJU.h"

uint32_t flag = 0;
uint32_t dis;
sbit K1 = P1^7;

uint8_t port = 1,port1 = 2,port2 = 3,port3 = 4;

//extern bit usart1_RI;
//extern uint8_t usart1_data;
////extern uint16_t D ;
//extern uint32_t miao;
//extern uint32_t System_us;

uint8_t flag1 = 0,flag2 = 0,flag3 = 0,flag4 = 0;
uint16_t M = 0,M1 = 1,M2 = 2;

uint8_t xdata str_buf1[128];


void CPU_int()
{
  timer1_init();
	usart_init();
	InitUltrasonicDistance();
	PWM_init();

	LCD_Init();     //1602��ʼ��
	LCD_Clear();
}



void main(void)
{ 
	CPU_int();	
	EN1 = 1;
	EN2 = 1;
	EX0	= 1;	//ʹ���ⲿ�ж�0
	EX1 = 1;	//ʹ���ⲿ�ж�1
	IT0 = 1;	//�����ⲿ�ж�0Ϊ�½��ش���
	IT1 = 1;	//�����ⲿ�ж�1Ϊ�½��ش���
	PX0 = 1;	//�����ⲿ�ж�0���ȼ�Ϊ��
	PX1 = 0;	//�����ⲿ�ж�1���ȼ�Ϊ��
	
	EA = 1;	
	
  EN1 = 0;
	EN2 = 0;	
	H_F1 = 0;			//ȫ��
	CW1 = 0;			//��ת	
	H_F2 = 0;			//ȫ��
	CW2 = 1;			//��ת	
	
	CLK1 = 1;
	CLK2 = 1;
	while(1)
	{		
		if(!flag)
		{
			if(!M)
			{
				find_road();
			}
			else
			{
				C_point();	
			}				
		}
		else
		{
			if(0 == flag2)
        chaoshengbo();						
			else	
				chaoshengbo_2();	
		}
		ShiZhong();
	}
}


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

	LCD_Init();     //1602初始化
	LCD_Clear();
}



void main(void)
{ 
	CPU_int();	
	EN1 = 1;
	EN2 = 1;
	EX0	= 1;	//使能外部中断0
	EX1 = 1;	//使能外部中断1
	IT0 = 1;	//设置外部中断0为下降沿触发
	IT1 = 1;	//设置外部中断1为下降沿触发
	PX0 = 1;	//设置外部中断0优先级为高
	PX1 = 0;	//设置外部中断1优先级为低
	
	EA = 1;	
	
  EN1 = 0;
	EN2 = 0;	
	H_F1 = 0;			//全步
	CW1 = 0;			//正转	
	H_F2 = 0;			//全步
	CW2 = 1;			//反转	
	
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


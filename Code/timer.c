#include <STC12C5A.H>
#include <INTRINS.h>
#include "timer.h"
#include "usart.h"
#include "1602.h"
#include "stdio.h"
#include "yundong.h"

uint8_t PWM1_val=0,PWM2_val=0,PWM1_set=11,PWM2_set=11;
extern uint32_t dis;
uint32_t step;
uint32_t sys_tm = 0,System_us = 0;
uint16_t miao;
 
uint16_t cout1,cout2,cout3;
uint8_t xdata str_buf[256];
 
extern uint8_t display[];
void timer1_init()
{
	TMOD &= 0x0f;
	TMOD |= 0x10;					//ģʽ1,16λ��ʱ��
	AUXR |= 0x40;					//1Tģʽ
	TH1 = (65536-FOSC*tm)>>8;		//1Tģʽ��ֵ
	TL1 = (65536-FOSC*tm);
	TR1 = 1;						//������ʱ��0����
	ET1 = 1;			  		//����ʱ��0�ж�
	PT1 = 1;            //
}

void delay_timer_ms(uint16_t ms)  
{
	uint32_t val=sys_tm+ms;
	while(sys_tm<=val)
		_nop_();
}


void pand(void)
{
	if(EN1 == 0)
	{			
		if(EN2 == 1) 
			cout1++;		//��ת
	}
	else
	{
		if(EN2 == 0) 
			cout2++;		//��ת
		if(EN2 == 1 && PWM1_set == PWM2_set)
			cout3++;    //ֱ��
	}
}


void Timer1_handle(void) interrupt 3
{
	static uint8_t tm_flag;
	System_us++;
	tm_flag = (tm_flag+1)%5;
	TH1 = (65536 - FOSC*tm)>>8;
	TL1 = 65536 - FOSC*tm;
	if(!tm_flag)
		sys_tm++;
	PWM1_val = (PWM1_val+1)%PWM1_set;
	PWM2_val = (PWM2_val+1)%PWM2_set;
	if(!PWM1_val)
	{	
		CLK1 = !CLK1;
	}
	if(!PWM2_val)
	{
		CLK2 = !CLK2;
		pand();
	}
	if(System_us == 5000)
	{
		miao++;
		System_us = 0;
//	  sprintf(str_buf,"The Receve char is:%d\r\n",miao);
//	  my_printf(str_buf);
  }
}

	
void ShiZhong()   //��ʾʱ��
{
	uint8_t i,j;
//	if(System_us == 5000)
//	{
//		miao++;
//		System_us = 0;
//  }
	if(99 == miao)
		miao = 0;
	i = miao%10;  //��ʾ����
	j = miao/10;	
//	sprintf(str_buf,"The Receve char is:%d\r\n",miao);
//	my_printf(str_buf);
//	LCD_Write_Com(0xcc);
//	LCD_Write_Data(display[j]);
//	LCD_Write_Data(display[i]);
}



void Set_PWM1(uint8_t val)	//val���ڵ����ٶȣ�ԽС�ٶ�Խ�� ����250�����3
{
	PWM1_set = val;
}

void Set_PWM2(uint8_t val)	//val���ڵ����ٶȣ�ԽС�ٶ�Խ��
{
	PWM2_set = val;
}

uint32_t Get_dis(void)
{
	dis = (11*step)/100;
	return dis;
}


uint32_t Get_miao()
{
	return miao;
}



#include <STC12C5A.H>
#include <1602.h>
#include <intrins.h>
#include "MY_DEFINE.H"
#include "timer.h"
#include "stdio.h"
#include "usart.h"


#define RS_CLR RS=0 
#define RS_SET RS=1

#define RW_CLR RW=0 
#define RW_SET RW=1 

#define EN_CLR EN=0
#define EN_SET EN=1

#define DataPort P0        
//extern uint8_t usart1_data;
extern uint32_t System_us;

extern uint16_t M;

uint16_t D = 0;

extern uint32_t flag;

uint8_t display[] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};
uint8_t display1[3],display2[3],display3[3];

extern uint8_t flag1,flag2,flag3,flag4;

void Delay_us(unsigned char t)
{
	while(--t); //T = t*2+5 us
}

void Delay_ms(unsigned char t)
{
	while(t--)
	{
		Delay_us(245);
		Delay_us(245);
  }
}


bit LCD_Check_Busy(void)  //��æ
{
//	DataPort = 0xFF;
	RS_CLR;
	RW_SET;
	EN_CLR;
	Delay_us(2);
	EN_SET;
	return(bit)(DataPort & 0x80);
}


void LCD_Write_Com(unsigned char com)   //д�����
{  
	 while(LCD_Check_Busy()); //æ��ȴ�
	 RS_CLR; 
	 RW_CLR; 
	 DataPort= com; 
		EN_SET; 
	 _nop_(); 
	 EN_CLR;
}

void LCD_Write_Data(unsigned char Data) //д����
{ 
	 while(LCD_Check_Busy()); //æ��ȴ�
	 RS_SET; 
	 RW_CLR;  
	 DataPort= Data; 
	 EN_SET; 
	_nop_();
	 EN_CLR;	
}

//void LCD_Write_Char(unsigned char x,unsigned char y,unsigned char Data)   //д���ַ�
// {     
// if (y == 0) 
// 	{     
// 	LCD_Write_Com(0x80 + x);     
// 	}    
// else 
// 	{     
// 	LCD_Write_Com(0xC0 + x);     
// 	}        
// LCD_Write_Data( Data);  
// }
// 
 
 
 
void LCD_Clear(void)   //����
 { 
	 LCD_Write_Com(0x01); 
	 Delay_ms(5);
 }
// 
 void lcd_pos(uint8_t pos)   //��ʾλ��
{                          
  LCD_Write_Com(pos | 0x80);  //����ָ��=80+��ַ����
}
 


void LCD_Init(void)        //��ʼ��
{
   LCD_Write_Com(0x38);    /*��ʾģʽ����*/ 
   Delay_ms(5); 
   LCD_Write_Com(0x38); 
   Delay_ms(5);
   LCD_Write_Com(0x38); 
   Delay_ms(5); 
   LCD_Write_Com(0x38);  
   LCD_Write_Com(0x08);    /*��ʾ�ر�*/ 
   LCD_Write_Com(0x01);    /*��ʾ����*/ 
   LCD_Write_Com(0x06);    /*��ʾ����ƶ�����*/ 
   Delay_ms(5);
   LCD_Write_Com(0x0C);    /*��ʾ�����������*/
}


//void xianshi(void)
//{
//	ShiZhong();
//	Show_num(D);
//}


void EXINT0_handle(void) interrupt 0  //�ⲿ�ж�
{ 
	EX0 = 0;
	Delay_ms(5);
	if(!P32)
	{
		if(Get_miao() < 5)
		 D++;
		else
			M = 1;
//		lcd_pos(0xcf);
//   	LCD_Write_Data(display[D]); 
	}
	EX0 = 1;
}

void Show_num(uint16_t d)
{
	switch(d)
	{
		 case 1:
		 display1[0] = Get_dis()%10;
		 display1[1] = (Get_dis()/10)%10;
		 display1[2] = Get_dis()/100;
		 LCD_Write_Com(0x40);
		 LCD_Write_Data(display1[2]);
		 LCD_Write_Data(display1[1]);
		 LCD_Write_Data(display1[0]);
		 break;
		 
		 case 2:
		 display2[0] = Get_dis()%10;
		 display2[1] = (Get_dis()/10)%10;
		 display2[2] = Get_dis()/100;
		 LCD_Write_Com(0x45);
		 LCD_Write_Data(display2[2]);
		 LCD_Write_Data(display2[1]);
		 LCD_Write_Data(display2[0]);
		 break;
		 
		 case 3:
		 display3[0] = Get_dis()%10;
		 display3[1] = (Get_dis()/10)%10;
		 display3[2] = Get_dis()/100;
		 LCD_Write_Com(0x49);
		 LCD_Write_Data(display3[2]);
		 LCD_Write_Data(display3[1]);
		 LCD_Write_Data(display3[0]);
		 break;
  }
}

void C_point(void)
{
	uint16_t t;
	EN1 = 0;
	EN2 = 0;
	for(t=0;t<5;t++)
	{
	delay_timer_ms(1000);
	}
	EN1 = 1;
	EN2 = 1;
	flag = 1;
}



#include <STC12C5A.H>
#include "usart.h"

//#define	FOSC		11059200L		//晶振频率 11.0582MHz
//#define	BAUD		115200			//串口波特率 可设为19200、9600等

bit usart1_busy=0;				//串口发送完成标志
bit usart1_RI = 0;				//串口接收完成标志
uint8_t usart1_data;			//串口接收数据

void usart_init()
{
	SCON = 0x50;					//模式1�,8位、波特率可变
	BRT = 256 - FOSC/BAUD/32;		//独立计数器初值
	AUXR |= 0x15;					//独立波特率计数器为1T模式，用于USART1，启动计数
	ES = 1;							//开串口中断
}


void T_sbuf(uint8_t chr)
{
	uint8_t t=0xff;
	while(usart1_busy && t--);
	SBUF = chr;
	usart1_busy=1;
}

void my_printf(uint8_t *str)
{
	do
	{
		T_sbuf(*str);
	}while(*(str++)!='\0');
}

void Uart1_handle(void) interrupt 4
{
	if(RI)
	{
		RI = 0;
		usart1_RI = 1;
		usart1_data = SBUF;
	}
	if(TI)
	{
		TI = 0;
		usart1_busy=0;
	}
}

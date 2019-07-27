#include <STC12C5A.H>
#include "usart.h"

//#define	FOSC		11059200L		//����Ƶ�� 11.0582MHz
//#define	BAUD		115200			//���ڲ����� ����Ϊ19200��9600��

bit usart1_busy=0;				//���ڷ�����ɱ�־
bit usart1_RI = 0;				//���ڽ�����ɱ�־
uint8_t usart1_data;			//���ڽ�������

void usart_init()
{
	SCON = 0x50;					//ģʽ1�,8λ�������ʿɱ�
	BRT = 256 - FOSC/BAUD/32;		//������������ֵ
	AUXR |= 0x15;					//���������ʼ�����Ϊ1Tģʽ������USART1����������
	ES = 1;							//�������ж�
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

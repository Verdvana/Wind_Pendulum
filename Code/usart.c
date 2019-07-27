#include <STC12C5A.H>
#include "usart.h"

//#define	FOSC		11059200L		//¾§ÕñÆµÂÊ 11.0582MHz
//#define	BAUD		115200			//´®¿Ú²¨ÌØÂÊ ¿ÉÉèÎª19200¡¢9600µÈ

bit usart1_busy=0;				//´®¿Ú·¢ËÍÍê³É±êÖ¾
bit usart1_RI = 0;				//´®¿Ú½ÓÊÕÍê³É±êÖ¾
uint8_t usart1_data;			//´®¿Ú½ÓÊÕÊı¾İ

void usart_init()
{
	SCON = 0x50;					//Ä£Ê½1£,8Î»¡¢²¨ÌØÂÊ¿É±ä
	BRT = 256 - FOSC/BAUD/32;		//¶ÀÁ¢¼ÆÊıÆ÷³õÖµ
	AUXR |= 0x15;					//¶ÀÁ¢²¨ÌØÂÊ¼ÆÊıÆ÷Îª1TÄ£Ê½£¬ÓÃÓÚUSART1£¬Æô¶¯¼ÆÊı
	ES = 1;							//¿ª´®¿ÚÖĞ¶Ï
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

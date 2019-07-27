#include <STC12C5A.H>
#include "PWM.h"

void PWM_init()
{
	TMOD &= 0xf0;
	TMOD |= 0x02;					//ģʽ2,8λ�Զ���װ��ʱ��
	AUXR &= ~0x80;					//12Tģʽ
	TH0 = 0xB8;	// 0xe7;						//12Tģʽ�£�PWMΪ400HZ�ĳ�ֵ
	TL0 = 0xB8;	//20msPWM	0xe7;
	TR0 = 1;						//������ʱ��0����
	
	CCON = 0;					//���־λ
	CMOD = 0x04;				//ѡ��PCAʱ��ԴΪ��ʱ��0����ź�
	CCAPM0 |= 0x42;
	CH = 0;
	CL = 0;
	CCAP0H = CCAP0L = (0xff - PWM_1_5MS);			//�������

//	PCA_PWM0 = 0;
	CR = 1;
}


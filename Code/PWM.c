#include <STC12C5A.H>
#include "PWM.h"

void PWM_init()
{
	TMOD &= 0xf0;
	TMOD |= 0x02;					//模式2,8位自动重装定时器
	AUXR &= ~0x80;					//12T模式
	TH0 = 0xB8;	// 0xe7;						//12T模式下，PWM为400HZ的初值
	TL0 = 0xB8;	//20msPWM	0xe7;
	TR0 = 1;						//启动定时器0计数
	
	CCON = 0;					//清标志位
	CMOD = 0x04;				//选择PCA时钟源为定时器0溢出信号
	CCAPM0 |= 0x42;
	CH = 0;
	CL = 0;
	CCAP0H = CCAP0L = (0xff - PWM_1_5MS);			//脉宽调制

//	PCA_PWM0 = 0;
	CR = 1;
}


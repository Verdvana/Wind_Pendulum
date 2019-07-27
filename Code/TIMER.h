#ifndef	__TIMER_H
#define	__TIMER_H
#include "my_define.h"

#define	tm		1/5000			//定时器时间 2ms


void timer1_init();
void delay_timer_ms(uint16_t ms);
void delay_us(uint16_t us);
void Timer_delay_us(uint16_t us);
void Set_PWM1(uint8_t val);
void Set_PWM2(uint8_t val);
uint32_t Get_dis(void);
void ShiZhong();
uint32_t Get_miao();

//extern  uint16_t cout1,cout2,cout3;
#endif
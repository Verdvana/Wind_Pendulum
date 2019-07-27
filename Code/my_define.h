#ifndef __MY_DEFINE_H
#define	__MY_DEFINE_H

typedef	unsigned long	uint32_t;
typedef unsigned int 	uint16_t;
typedef unsigned char 	uint8_t;

typedef	long			int32_t;
typedef int 			int16_t;
typedef char 			int8_t;

sbit EN1 = P2^3;				//左电机
sbit H_F1 = P2^2;
sbit CW1 = P2^1;
sbit CLK1 = P2^0;

sbit EN2 = P2^7;				//右电机
sbit H_F2 = P2^6;
sbit CW2 = P2^5;
sbit CLK2 = P2^4;

//sbit INB = P0^7;
//sbit INA = P0^6;

sbit RS = P3^5;   //1602
sbit RW = P3^6;
sbit EN = P3^7;

sbit LED0 = P1^5;
//sbit LED1 = P0^1;

sbit RX =P1^4; //Echo  
sbit TX =P1^3;

sbit RX1 =P1^5; //Echo  
sbit TX1 =P1^6;

#define	FOSC		11059200L		//晶振频率 11.0582MHz
#define	BAUD		115200			//串口波特率 可设为19200、9600等


#define PWM_RIGHT	11	//右转90度		6
#define	PWM_LEFT	25	//左转90度		30
#define PWM_MIDDLE 18

#define PWM_1MS	12	//
#define	PWM_2MS	24	//
#define PWM_1_5MS 18

#endif

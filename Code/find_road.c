#include <STC12C5A.H>
#include "timer.h"
#include "PWM.h"
#include "find_road.h"
#include "1602.h"

void find_road()
{
	switch(P1 & 0x07)
	{
		case 0x07:
			
		case 0x02:  //�м�
			Set_PWM1(11);
		  Set_PWM2(11);
		  EN1 = EN2 = 1;
		 break;
		case 0x06: //��С
			Set_PWM1(17);
		  Set_PWM2(11);
		  EN1 = EN2 = 1;
		 break;
		case 0x04: //��С
			Set_PWM1(17);
		  Set_PWM2(11);
		  EN1 = EN2 = 1;
		 break;
		case 0x03: //��С
		  Set_PWM1(11); 
		  Set_PWM2(17);
		  EN1 = EN2 = 1;
		 break;
		case 0x01: //��С
			Set_PWM1(11); 
		  Set_PWM2(17);
		  EN1 = EN2 = 1;
		 break;
		default:
			EN1 = EN2 = 1;
		 break;
  }
}




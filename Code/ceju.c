#include <STC12C5A60S2.H>
#include <intrins.h>  
#include "ceju.h"  
#include <STDIO.H> 
#include "usart.h"
#include "yundong.h"
#include "find_road.h"
#include "timer.h"
 
#define uchar unsigned char  

#define DOUBLE_CRYSTAL_FREQ 11.0592 

#define iMAX_LEN 21684  
#define iMIN_LEN 109  
  
unsigned int miDistance=0; //测距的距离值 
uchar mcDistanceErr=0; //测距错误标记 
bit mbDelayOverFlg = 1; //延迟程序的控制标记 
uchar mbDelay10H, mbDelay10L; //测距的小单位时间延迟 

uint8_t xdata show_buf[128];
unsigned int iOld=0;	

uint16_t K1 = 1,K2 = 2,K3 = 3,K4 = 4,K5 = 5,K6 = 6,K7 = 7;
 
extern uint8_t flag1,flag2,flag3;
/*------------------------------------------------------- 
 *初始化函数
 *@return void 
 *-------------------------------------------------------*/  
void InitUltrasonicDistance(void)  
{  
    unsigned int iTmp;  
  
    TMOD |=0x01; //
    
    TH0=0; // 
    TL0=0; //  
    TR0=0; //  
    ET0=1; //  
  
    iTmp = (unsigned int)(65536-(10000/(12/DOUBLE_CRYSTAL_FREQ))); //10ms???????  
    mbDelay10H = iTmp >> 8; //?8??  
    mbDelay10L = iTmp &0x0F; //?8??  
}  
  
/**------------------------------------------------------- 
 * 定时器函数，T0计数器使用1号中断
 *   ??:????????,???????,????>60ms 
 *         ?????????,time=65.535ms,mbDelayCtlFlg=1 
 * -------------------------------------------------------  
*/  
void tim0_()interrupt 1  
{    
    TR0 = 0; //T0?????  
    mbDelayOverFlg = 1; //??????  
}  
  
/*------------------------------------------------------- 
 *启动超声波测距模块，TX保持22us的高电平
 *-------------------------------------------------------*/  
void StartModule()  
{  
    TX = 1; //控制端1  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    TX=0; //控制端置0，等待接收回波 
}  
  
void StartModule_1()  
{  
    TX1 = 1; //控制端1  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    _nop_();  
    TX1=0; //控制端置0，等待接收回波 
}  

/*------------------------------------------------------- 
 *获取最近一次测得的距离 
 *  ??:??????,????100ms-150ms???? 
 *-------------------------------------------------------*/  
unsigned int getDistance(void)  
{  	
    return miDistance;
				sprintf(show_buf,"CESHI : %d",K1);
				my_printf(show_buf);	  
} 

  
/*------------------------------------------------------- 
 *获取最近一次测距的状态
 *@return unsigned int 0:?? / 1:(err)???? /2:(err)??? 
 *-------------------------------------------------------*/  
unsigned int getDistanceState(void)  
{   	
    return mcDistanceErr; 

}  
  
/*------------------------------------------------------- 
 *检查测距操作 
 *  ??:????????,????getDistance()?getDistanceState()???? 
 *  ??:??????,????100ms-150ms???? 
 * @return 0:?????? / 1:????????????? 
 *-------------------------------------------------------*/  
unsigned char refreshDistance(void)  
{
    unsigned int i; //超量程检测变量  
    unsigned int iCycle; //计算总周期 
    if (1 == mbDelayOverFlg)//判断是否在延迟期  
    {     
        i = iMAX_LEN; //置入最大的量程  
        StartModule(); //发送测距模块的启动信号  
        while(!RX && i-->0);  
        //判断结果 
        if (i>0) //小于N米  
        {				
            TR0=1; //收到回波的上边沿(RX=1),打开计数器 
            while(RX);//当回波RX=0时，测距结束
            TR0=0; //关闭定时器(需要一个时钟周期)  nnnnnnn
            iCycle = (TH0 * 256 + TL0) + 1;					//计算总消耗的周期
            TH0=0;  
            TL0=0;  
      
            if (iCycle <= iMIN_LEN)  
            {  
                mcDistanceErr = 1;//距离太近 
                mbDelayOverFlg = 0; //复位延迟标志 
                TH0 = mbDelay10H; //重装计数器高8  
                TL0 = mbDelay10L; //重装计数器低8位
                TR0 = 1; //启动延迟计数器 
            }  
            else  
            {  
                //(iCycle * 1.0851 * 0.17 / 10) => iCycle * 0.01844670   
                miDistance = (unsigned int)(iCycle * 0.01844670);//(??cm)  
                mcDistanceErr = 0;//测距正常值   
                mbDelayOverFlg = 0; //复位延迟标志  
                TH0 = 0; //T0,高位复位  
                TL0 = 0; //T0,地位复位 
                TR0=1;//打开延迟计数器(此时不测距,所以不影响测距的计算)
            }  
        }  
        else   
            mcDistanceErr = 2; //超量程  
  
        return 0; //完成测距操作 
    }  
    else //正在延迟等待下一次的测距  
        return 1;  
}




unsigned char refreshDistance_2(void)  
{
    unsigned int i; //超量程检测变量  
    unsigned int iCycle; //计算总周期 
    if (1 == mbDelayOverFlg)//判断是否在延迟期  
    {     
        i = iMAX_LEN; //置入最大的量程  
        StartModule_1(); //发送测距模块的启动信号  
        while(!RX1 && i-->0);  
        //判断结果 
        if (i>0) //小于N米  
        {				
            TR0=1; //收到回波的上边沿(RX=1),打开计数器 
            while(RX1);//当回波RX=0时，测距结束
            TR0=0; //关闭定时器(需要一个时钟周期)  nnnnnnn
            iCycle = (TH0 * 256 + TL0) + 1;					//计算总消耗的周期
            TH0=0;  
            TL0=0;  
      
            if (iCycle <= iMIN_LEN)  
            {  
                mcDistanceErr = 1;//距离太近 
                mbDelayOverFlg = 0; //复位延迟标志 
                TH0 = mbDelay10H; //重装计数器高8  
                TL0 = mbDelay10L; //重装计数器低8位
                TR0 = 1; //启动延迟计数器 
            }  
            else  
            {  
                //(iCycle * 1.0851 * 0.17 / 10) => iCycle * 0.01844670   
                miDistance = (unsigned int)(iCycle * 0.01844670);//(??cm)  
                mcDistanceErr = 0;//测距正常值   
                mbDelayOverFlg = 0; //复位延迟标志  
                TH0 = 0; //T0,高位复位  
                TL0 = 0; //T0,地位复位 
                TR0=1;//打开延迟计数器(此时不测距,所以不影响测距的计算)
            }  
        }  
        else   
            mcDistanceErr = 2; //超量程  
  
        return 0; //完成测距操作 
    }  
    else //正在延迟等待下一次的测距  
        return 1;  
}




void chaoshengbo(void)  
{      			

	
		//当调用测距函数后，返回值为0，表示测距成功，否则测距函数正在延迟中  
			if (0 == refreshDistance())  
			{  
					//当取值有效时，如果与前次没有变化，则不作更新
					if (0 == getDistanceState() && (iOld != getDistance()))				
					{					
						iOld = getDistance(); 
						sprintf(show_buf,"JuLi is : %d",iOld);
						my_printf(show_buf);	
						if(iOld < 10)
						{
//							flag1 = 1;
//							left(480,&flag1);
							unsigned int miDistance=0;
							uchar mcDistanceErr=0;
							flag2 = 1;
						}					
				}  
			}         
}  


void chaoshengbo_2(void)  
{    
		//当调用测距函数后，返回值为0，表示测距成功，否则测距函数正在延迟中  
		if (0 == refreshDistance_2())  
		{  

				//当取值有效时，如果与前次没有变化，则不作更新
				if (0 == getDistanceState() && (iOld != getDistance()))  
				{  
						iOld = getDistance(); 
						sprintf(show_buf,"JuLi22 is : %d",iOld);
						my_printf(show_buf);
//						if(iOld < 10)
//						{
//							Set_PWM1(17);
//							Set_PWM2(11);
//							EN1 = EN2 = 1;
//						}
//						else
//						{
//							Set_PWM1(11); 
//							Set_PWM2(17);
//							EN1 = EN2 = 1;
//						}
				}  
		}         
}  


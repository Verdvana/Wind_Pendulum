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
  
unsigned int miDistance=0; //���ľ���ֵ 
uchar mcDistanceErr=0; //�������� 
bit mbDelayOverFlg = 1; //�ӳٳ���Ŀ��Ʊ�� 
uchar mbDelay10H, mbDelay10L; //����С��λʱ���ӳ� 

uint8_t xdata show_buf[128];
unsigned int iOld=0;	

uint16_t K1 = 1,K2 = 2,K3 = 3,K4 = 4,K5 = 5,K6 = 6,K7 = 7;
 
extern uint8_t flag1,flag2,flag3;
/*------------------------------------------------------- 
 *��ʼ������
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
 * ��ʱ��������T0������ʹ��1���ж�
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
 *�������������ģ�飬TX����22us�ĸߵ�ƽ
 *-------------------------------------------------------*/  
void StartModule()  
{  
    TX = 1; //���ƶ�1  
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
    TX=0; //���ƶ���0���ȴ����ջز� 
}  
  
void StartModule_1()  
{  
    TX1 = 1; //���ƶ�1  
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
    TX1=0; //���ƶ���0���ȴ����ջز� 
}  

/*------------------------------------------------------- 
 *��ȡ���һ�β�õľ��� 
 *  ??:??????,????100ms-150ms???? 
 *-------------------------------------------------------*/  
unsigned int getDistance(void)  
{  	
    return miDistance;
				sprintf(show_buf,"CESHI : %d",K1);
				my_printf(show_buf);	  
} 

  
/*------------------------------------------------------- 
 *��ȡ���һ�β���״̬
 *@return unsigned int 0:?? / 1:(err)???? /2:(err)??? 
 *-------------------------------------------------------*/  
unsigned int getDistanceState(void)  
{   	
    return mcDistanceErr; 

}  
  
/*------------------------------------------------------- 
 *�������� 
 *  ??:????????,????getDistance()?getDistanceState()???? 
 *  ??:??????,????100ms-150ms???? 
 * @return 0:?????? / 1:????????????? 
 *-------------------------------------------------------*/  
unsigned char refreshDistance(void)  
{
    unsigned int i; //�����̼�����  
    unsigned int iCycle; //���������� 
    if (1 == mbDelayOverFlg)//�ж��Ƿ����ӳ���  
    {     
        i = iMAX_LEN; //������������  
        StartModule(); //���Ͳ��ģ��������ź�  
        while(!RX && i-->0);  
        //�жϽ�� 
        if (i>0) //С��N��  
        {				
            TR0=1; //�յ��ز����ϱ���(RX=1),�򿪼����� 
            while(RX);//���ز�RX=0ʱ��������
            TR0=0; //�رն�ʱ��(��Ҫһ��ʱ������)  nnnnnnn
            iCycle = (TH0 * 256 + TL0) + 1;					//���������ĵ�����
            TH0=0;  
            TL0=0;  
      
            if (iCycle <= iMIN_LEN)  
            {  
                mcDistanceErr = 1;//����̫�� 
                mbDelayOverFlg = 0; //��λ�ӳٱ�־ 
                TH0 = mbDelay10H; //��װ��������8  
                TL0 = mbDelay10L; //��װ��������8λ
                TR0 = 1; //�����ӳټ����� 
            }  
            else  
            {  
                //(iCycle * 1.0851 * 0.17 / 10) => iCycle * 0.01844670   
                miDistance = (unsigned int)(iCycle * 0.01844670);//(??cm)  
                mcDistanceErr = 0;//�������ֵ   
                mbDelayOverFlg = 0; //��λ�ӳٱ�־  
                TH0 = 0; //T0,��λ��λ  
                TL0 = 0; //T0,��λ��λ 
                TR0=1;//���ӳټ�����(��ʱ�����,���Բ�Ӱ����ļ���)
            }  
        }  
        else   
            mcDistanceErr = 2; //������  
  
        return 0; //��ɲ����� 
    }  
    else //�����ӳٵȴ���һ�εĲ��  
        return 1;  
}




unsigned char refreshDistance_2(void)  
{
    unsigned int i; //�����̼�����  
    unsigned int iCycle; //���������� 
    if (1 == mbDelayOverFlg)//�ж��Ƿ����ӳ���  
    {     
        i = iMAX_LEN; //������������  
        StartModule_1(); //���Ͳ��ģ��������ź�  
        while(!RX1 && i-->0);  
        //�жϽ�� 
        if (i>0) //С��N��  
        {				
            TR0=1; //�յ��ز����ϱ���(RX=1),�򿪼����� 
            while(RX1);//���ز�RX=0ʱ��������
            TR0=0; //�رն�ʱ��(��Ҫһ��ʱ������)  nnnnnnn
            iCycle = (TH0 * 256 + TL0) + 1;					//���������ĵ�����
            TH0=0;  
            TL0=0;  
      
            if (iCycle <= iMIN_LEN)  
            {  
                mcDistanceErr = 1;//����̫�� 
                mbDelayOverFlg = 0; //��λ�ӳٱ�־ 
                TH0 = mbDelay10H; //��װ��������8  
                TL0 = mbDelay10L; //��װ��������8λ
                TR0 = 1; //�����ӳټ����� 
            }  
            else  
            {  
                //(iCycle * 1.0851 * 0.17 / 10) => iCycle * 0.01844670   
                miDistance = (unsigned int)(iCycle * 0.01844670);//(??cm)  
                mcDistanceErr = 0;//�������ֵ   
                mbDelayOverFlg = 0; //��λ�ӳٱ�־  
                TH0 = 0; //T0,��λ��λ  
                TL0 = 0; //T0,��λ��λ 
                TR0=1;//���ӳټ�����(��ʱ�����,���Բ�Ӱ����ļ���)
            }  
        }  
        else   
            mcDistanceErr = 2; //������  
  
        return 0; //��ɲ����� 
    }  
    else //�����ӳٵȴ���һ�εĲ��  
        return 1;  
}




void chaoshengbo(void)  
{      			

	
		//�����ò�ຯ���󣬷���ֵΪ0����ʾ���ɹ��������ຯ�������ӳ���  
			if (0 == refreshDistance())  
			{  
					//��ȡֵ��Чʱ�������ǰ��û�б仯����������
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
		//�����ò�ຯ���󣬷���ֵΪ0����ʾ���ɹ��������ຯ�������ӳ���  
		if (0 == refreshDistance_2())  
		{  

				//��ȡֵ��Чʱ�������ǰ��û�б仯����������
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


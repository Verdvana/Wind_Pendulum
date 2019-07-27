#ifndef __1602__H
#define __1602__H

void Delay_us(unsigned char t);
void Delay_ms(unsigned char t);
bit LCD_Check_Busy(void);
void LCD_Write_Com(unsigned char com);
void LCD_Write_Data(unsigned char Data);
void LCD_Write_Char(unsigned char x,unsigned char y,unsigned char Data);
void LCD_Clear(void);
void LCD_Init(void);
void Show_num(unsigned int  D);
void C_point();
//void lcd_pos(unsigned char pos);
//void xianshi(void);

#endif


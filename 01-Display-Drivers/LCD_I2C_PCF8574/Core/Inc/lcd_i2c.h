#ifndef LCD_H
#define LCD_H

#include "stm32f4xx_hal.h"

void LCD_Init(I2C_HandleTypeDef *hi2c);
void LCD_Send_Cmd(char cmd);
void LCD_Send_Char(char data);
void LCD_Send_String(char *str);
void LCD_Set_Cursor(int row, int col);
void LCD_Send_Integer(int num);
void LCD_Clear(void);
// Note: To use LCD_Send_Float, you need to enable float support for printf in linker settings.
void LCD_Send_Float(float num, int precision);

#endif

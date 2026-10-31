/*
 * lcd_i2c.h
 *
 *  Created on: Nov 3, 2025
 *      Author: DELL
 */

#ifndef I2C_LCD_H
#define I2C_LCD_H

#include "stm32f4xx_hal.h"

void LCD_Init(I2C_HandleTypeDef *hi2c);
void LCD_Send_Cmd(char cmd);
void LCD_Send_Char(char data);
void LCD_Send_String(char *str);
void LCD_Set_Cursor(int row, int col);
void LCD_Shift_Left(void);
void LCD_Shift_Right(void);
void LCD_Send_Integer(int num);
void LCD_Send_Float(float num,int precision);
void LCD_Clear(void);

#endif

/** oled.h */
#ifndef __OLED_H__
#define __OLED_H__

#include "stm32f4xx_hal.h"
#include <stdint.h>

#define OLED_EXP_CHAR_LENGTH 6

void OLED_Init(void);
void OLED_Send_Command(uint8_t cmd);
void OLED_Send_Data(uint8_t data);
void OLED_Set_Cursor(uint8_t x, uint8_t y);
void OLED_Clear(void);
void OLED_Send_String(const char *str);
void OLED_Send_Char(char ch);
void OLED_Send_Integer(int value);
void OLED_Send_Float(float num, int precision);
void OLED_Draw_Bitmap(const uint8_t *bitmap, uint8_t width, uint8_t height);

extern const uint8_t logo_bitmap[1024];
extern const uint8_t asciiTable[][OLED_EXP_CHAR_LENGTH];

#endif

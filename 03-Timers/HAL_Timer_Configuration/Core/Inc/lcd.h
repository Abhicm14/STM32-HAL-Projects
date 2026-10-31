
#ifndef LCD_H_
#define LCD_H_

#include "stm32f4xx.h"  // Adjust this according to your STM32 series

// Pin configuration for LCD
#define LCD_RS_Pin GPIO_PIN_8
#define LCD_RS_GPIO_Port GPIOE
#define LCD_E_Pin  GPIO_PIN_14
#define LCD_E_GPIO_Port GPIOE
#define LCD_D4_Pin GPIO_PIN_10
#define LCD_D4_GPIO_Port GPIOE
#define LCD_D5_Pin GPIO_PIN_11
#define LCD_D5_GPIO_Port GPIOE
#define LCD_D6_Pin GPIO_PIN_12
#define LCD_D6_GPIO_Port GPIOE
#define LCD_D7_Pin GPIO_PIN_13
#define LCD_D7_GPIO_Port GPIOE

// Function prototypes
void LCD_Init(void);
void LCD_Send_Command(uint8_t cmd);
void LCD_Send_Char(char data);
void LCD_Send_String(char *str);
void LCD_Set_Cursor(uint8_t row, uint8_t col);
void LCD_Clear(void);
void LCD_Send_Float(float num,int precision);
void LCD_Send_Integer(int value);

#endif /* LCD_H_ */

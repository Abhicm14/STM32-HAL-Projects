
#include "lcd.h"
#include "stm32f4xx.h"
#include <string.h>
#include <stdio.h>

// Function to send a command to the LCD
void LCD_Send_Command(uint8_t cmd) {
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);  // RS = 0 for command
    HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET);

    // Send upper nibble
    HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (cmd & 0x10) >> 4);
    HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (cmd & 0x20) >> 5);
    HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (cmd & 0x40) >> 6);
    HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (cmd & 0x80) >> 7);

    HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET);

    // Send lower nibble
    HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, cmd & 0x01);
    HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (cmd & 0x02) >> 1);
    HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (cmd & 0x04) >> 2);
    HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (cmd & 0x08) >> 3);

    HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
}

// Function to send data (characters) to the LCD
void LCD_Send_Char(char data)
{
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);  // RS = 1 for data
    HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET);

    // Send upper nibble
    HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (data & 0x10) >> 4);
    HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (data & 0x20) >> 5);
    HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (data & 0x40) >> 6);
    HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (data & 0x80) >> 7);

    HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET);

    // Send lower nibble
    HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, data & 0x01);
    HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (data & 0x02) >> 1);
    HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (data & 0x04) >> 2);
    HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (data & 0x08) >> 3);

    HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
}


// Function to initialize the LCD
void LCD_Init(void) {
    HAL_Delay(50);  // Wait for LCD power-up

    LCD_Send_Command(0x02);  // Initialize in 4-bit mode
    LCD_Send_Command(0x28);  // 2 line, 5x7 matrix
    LCD_Send_Command(0x0C);  // Display on, cursor off
    LCD_Send_Command(0x00);
    //crement cursor (shift right)
    LCD_Send_Command(0x01);  // Clear display
    HAL_Delay(2);
}

// Function to set the cursor position on the LCD
void LCD_Set_Cursor(uint8_t row, uint8_t col)
{
    uint8_t cmd = 0x80;
    if (row == 1)
    {
        cmd = 0xC0;
    }
    cmd += col;
    LCD_Send_Command(cmd);
}

// Function to send a string to the LCD
void LCD_Send_String(char *str)
{
    while (*str)
    {
        LCD_Send_Char(*str);
        str++;
    }
}

// Function to clear the LCD screen
void LCD_Clear(void)
{
    LCD_Send_Command(0x01);  // Clear display
    HAL_Delay(2);
}


void LCD_Send_Float(float num,int precision)
{
	 char buffer[16];
	 char format[10];// Buffer to hold the formatted string

	    // Convert the float to a string with 2 decimal places (you can adjust the precision)
	 sprintf(format, "%%.%df", precision);
	 sprintf(buffer,format,num);
	 LCD_Send_String(buffer);


}
void LCD_Send_Integer(int value)
{
    char buffer[16];  // Buffer to hold the integer as a string
    sprintf(buffer, "%d", value);  // Convert integer to string
    LCD_Send_String(buffer);  // Display the string on LCD
}



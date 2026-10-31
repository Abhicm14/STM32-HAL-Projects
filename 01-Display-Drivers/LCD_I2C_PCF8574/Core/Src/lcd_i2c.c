#include "lcd_i2c.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

#define LCD_ADDR 0x27 << 1  // Change this if scanner gives a different address
#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE_BIT 0x04

I2C_HandleTypeDef *i2c_handle;

void LCD_Send(uint8_t data, uint8_t mode)
{
    uint8_t high_nibble = data & 0xF0;
    uint8_t low_nibble = (data << 4) & 0xF0;
    uint8_t control = LCD_BACKLIGHT | mode;

    uint8_t data_arr[4] =
    {
        high_nibble | control | LCD_ENABLE_BIT,
        high_nibble | control,
        low_nibble | control | LCD_ENABLE_BIT,
        low_nibble | control
    };

    HAL_I2C_Master_Transmit(i2c_handle, LCD_ADDR, data_arr, 4, HAL_MAX_DELAY);
    HAL_Delay(1);
}

void LCD_Send_Cmd(char cmd)
{
    LCD_Send(cmd, 0x00);
}

void LCD_Send_Char(char data)
{
    LCD_Send(data, 0x01);
}

void LCD_Send_String(char *str)
{
    while (*str) LCD_Send_Char(*str++);
}

void LCD_Set_Cursor(int row, int col)
{
    uint8_t row_offsets[] = {0x80, 0xC0, 0x94, 0xD4};
    LCD_Send_Cmd(row_offsets[row] + col);
}

void LCD_Init(I2C_HandleTypeDef *hi2c)
{
    i2c_handle = hi2c;  // Store the I2C handle for communication
    HAL_Delay(50);      // Initial delay for LCD power stabilization

    // Initialize LCD in 4-bit mode
    LCD_Send_Cmd(0x33); // Initialize LCD in 8-bit mode (required step)
    LCD_Send_Cmd(0x32); // Switch to 4-bit mode

    LCD_Send_Cmd(0x28); // 4-bit mode, 2-line display, 5x8 dots font
    LCD_Send_Cmd(0x0C); // Display ON, Cursor OFF, Blink OFF
    LCD_Send_Cmd(0x06); // Increment cursor position, no display shift
    LCD_Send_Cmd(0x01); // Clear display and reset cursor
}

void LCD_Clear(void)
{
	LCD_Send_Cmd(0x01);
}
void LCD_Send_Integer(int num)
{
    char buffer[12];  // Buffer to hold the integer as a string
    sprintf(buffer, "%d", num);  // Convert integer to string
    LCD_Send_String(buffer);  // Send to LCD
}

//void LCD_Send_Float(float num, int precision)
//{
//    char buffer[20];  // Buffer to hold the float as a string
//    sprintf(buffer, "%.*f", precision, num);  // Convert float to string with specified decimal places
//    LCD_Send_String(buffer);  // Send to LCD
//}

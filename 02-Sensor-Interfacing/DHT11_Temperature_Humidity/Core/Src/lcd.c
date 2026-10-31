
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

void LCD_Scroll_Text(const char *text, uint8_t row, uint16_t delay_ms)
{
    char padded[64] = {0};
    snprintf(padded, sizeof(padded), "%-32s", text);  // pad with spaces

    char display[17] = {0};

    for (int i = 0; i < strlen(padded) - 15; i++) {
        strncpy(display, &padded[i], 16);
        display[16] = '\0';

        LCD_Set_Cursor(row, 0);
        LCD_Send_String(display);
        HAL_Delay(delay_ms);
    }
}

void LCD_Scroll_Text_Loop(const char *text, uint8_t row, uint16_t delay_ms)
{
    char looped[64];
    snprintf(looped, sizeof(looped), "%s   %s", text, text);  // wrap with spaces and repeat

    char display[17] = {0};
    int len = strlen(text);

    for (int i = 0;; i++) {
        int idx = i % (len + 3);
        strncpy(display, &looped[idx], 16);
        display[16] = '\0';

        LCD_Set_Cursor(row, 0);
        LCD_Send_String(display);
        HAL_Delay(delay_ms);
    }
}

void LCD_Create_Custom_Char(uint8_t location, uint8_t charmap[])
{
    //location &= 0x07; // Only 8 locations (0-7) are available
    LCD_Send_Command(0x40 | (location << 7)); // Set CGRAM address

    for (int i = 0; i < 8; i++)
    {
        LCD_Send_Char(charmap[i]); // Send each row of the custom char
    }
}

void LCD_Print_Custom_Char(uint8_t location)
{
    LCD_Send_Char(location); // Just send the index to print the character
}



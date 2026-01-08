#ifndef LCD_H
#define LCD_H

#include <stdint.h>

/* Initialize LCD module */
void LCD_Init(void);

/* Send command byte to LCD */
void LCD_Command(uint8_t cmd);

/* Write a single character to LCD */
void LCD_WriteChar(char c);

/* Write a string to LCD */
void LCD_PrintString(const char *s);

/* Clear LCD display */
void LCD_Clear(void);

/* Set cursor position on LCD */
void LCD_SetCursor(uint8_t row, uint8_t col);

#endif

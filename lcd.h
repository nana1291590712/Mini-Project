#ifndef LCD_H
#define LCD_H

#include <stdint.h>

void LCD_Init(void);
void LCD_Command(uint8_t cmd);
void LCD_WriteChar(char c);
void LCD_PrintString(const char *s);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);

#endif

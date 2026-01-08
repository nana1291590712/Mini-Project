#include "lcd.h"
#include "delay.h"
#include <stdint.h>

/* GPIO data registers used for LCD control and data */
#define GPIO_PORTA_DATA_R   (*((volatile uint32_t *)0x400043FC))
#define GPIO_PORTB_DATA_R   (*((volatile uint32_t *)0x400053FC))

/* LCD control signals connected to port A */
#define LCD_RS  0x04
#define LCD_RW  0x08
#define LCD_EN  0x10

/* Generate enable pulse for LCD */
static void LCD_PulseEnable(void)
{
    GPIO_PORTA_DATA_R |= LCD_EN;
    Delay_ms(1);
    GPIO_PORTA_DATA_R &= ~LCD_EN;
}

/* Send command instruction to LCD */
void LCD_Command(uint8_t cmd)
{
    GPIO_PORTA_DATA_R &= ~(LCD_RS | LCD_RW);
    GPIO_PORTB_DATA_R = cmd;
    LCD_PulseEnable();
    Delay_ms(2);
}

/* Write one character to LCD data register */
void LCD_WriteChar(char c)
{
    GPIO_PORTA_DATA_R |= LCD_RS;
    GPIO_PORTA_DATA_R &= ~LCD_RW;
    GPIO_PORTB_DATA_R = (uint8_t)c;
    LCD_PulseEnable();
    Delay_ms(2);
}

/* Write a null terminated string to LCD */
void LCD_PrintString(const char *s)
{
    while (*s)
    {
        LCD_WriteChar(*s++);
    }
}

/* Clear LCD display and reset cursor */
void LCD_Clear(void)
{
    LCD_Command(0x01);
    Delay_ms(2);
}

/* Set LCD cursor to specified row and column */
void LCD_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t addr = (row == 0) ? col : (0x40 + col);
    LCD_Command(0x80 | addr);
}

/* Initialize LCD in eight bit mode */
void LCD_Init(void)
{
    Delay_ms(20);

    LCD_Command(0x38);
    LCD_Command(0x0C);
    LCD_Command(0x06);
    LCD_Clear();
}

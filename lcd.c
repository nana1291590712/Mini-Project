#include "lcd.h"
#include "delay.h"
#include <stdint.h>

/* ================= GPIO ??(????????) ================= */
/* Port A:LCD ??? */
#define GPIO_PORTA_DATA_R   (*((volatile uint32_t *)0x400043FC))

/* Port B:LCD ??? D0–D7(8-bit) */
#define GPIO_PORTB_DATA_R   (*((volatile uint32_t *)0x400053FC))

/* LCD ???(??????????) */
#define LCD_RS  0x04   // PA2
#define LCD_RW  0x08   // PA3
#define LCD_EN  0x10   // PA4

/* ================= ???? ================= */
static void LCD_PulseEnable(void)
{
    GPIO_PORTA_DATA_R |= LCD_EN;
    Delay_ms(1);
    GPIO_PORTA_DATA_R &= ~LCD_EN;
}

/* ================= ???? ================= */

void LCD_Command(uint8_t cmd)
{
    GPIO_PORTA_DATA_R &= ~(LCD_RS | LCD_RW);  // RS=0, RW=0
    GPIO_PORTB_DATA_R = cmd;                  // 8-bit ??
    LCD_PulseEnable();
    Delay_ms(2);                              // ??????
}

void LCD_WriteChar(char c)
{
    GPIO_PORTA_DATA_R |= LCD_RS;              // RS=1
    GPIO_PORTA_DATA_R &= ~LCD_RW;             // RW=0
    GPIO_PORTB_DATA_R = (uint8_t)c;           // 8-bit ??
    LCD_PulseEnable();
    Delay_ms(2);
}

void LCD_PrintString(const char *s)
{
    while (*s)
    {
        LCD_WriteChar(*s++);
    }
}

void LCD_Clear(void)
{
    LCD_Command(0x01);    // Clear display
    Delay_ms(2);
}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t addr = (row == 0) ? col : (0x40 + col);
    LCD_Command(0x80 | addr);
}

/* ================= ???(8-bit) ================= */

void LCD_Init(void)
{
    Delay_ms(20);          // ????

    LCD_Command(0x38);     // ? 8-bit, 2 lines(??)
    LCD_Command(0x0C);     // Display ON, cursor OFF
    LCD_Command(0x06);     // Entry mode
    LCD_Clear();
}

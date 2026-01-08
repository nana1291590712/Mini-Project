#include "keypad.h"
#include "delay.h"
#include <stdint.h>

/* GPIO data register for keypad column outputs */
#define GPIO_PORTD_DATA_R   (*((volatile uint32_t *)0x400073FC))

/* GPIO data register for keypad row inputs */
#define GPIO_PORTE_DATA_R   (*((volatile uint32_t *)0x400243FC))

/* Key mapping table for four by four keypad */
static const char keymap[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

/* Scan keypad matrix and detect a single key press */
char Keypad_GetKey(void)
{
    int col, row;
    uint32_t rows;

    for (col = 0; col < 4; col++)
    {
        /* Set one column high and keep other columns low */
        GPIO_PORTD_DATA_R &= ~0x0F;
        GPIO_PORTD_DATA_R |= (1U << col);
        Delay_ms(1);

        /* Read row input states */
        rows = GPIO_PORTE_DATA_R & 0x0F;

        /* Check whether any row is active */
        if (rows != 0)
        {
            for (row = 0; row < 4; row++)
            {
                if (rows & (1U << row))
                {
                    char key = keymap[row][col];

                    /* Wait until key is released */
                    while (GPIO_PORTE_DATA_R & (1U << row)) { }
                    Delay_ms(20);

                    /* Clear column outputs after key detection */
                    GPIO_PORTD_DATA_R &= ~0x0F;

                    return key;
                }
            }
        }
    }

    /* Clear all column outputs when no key is detected */
    GPIO_PORTD_DATA_R &= ~0x0F;
    return 0;
}

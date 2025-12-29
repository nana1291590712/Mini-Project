#include "keypad.h"
#include "delay.h"
#include <stdint.h>

/* Port D: Columns PD0–PD3 */
#define GPIO_PORTD_DATA_R   (*((volatile uint32_t *)0x400073FC))

/* Port E: Rows PE0–PE3 */
#define GPIO_PORTE_DATA_R   (*((volatile uint32_t *)0x400243FC))

static const char keymap[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

/* ???:???,?????;???? 0 */
char Keypad_GetKey(void)
{
    int col, row;
    uint32_t rows;

    for (col = 0; col < 4; col++)
    {
        /* ???=1,???=0(???) */
        GPIO_PORTD_DATA_R &= ~0x0F;
        GPIO_PORTD_DATA_R |= (1U << col);
        Delay_ms(1);

        rows = GPIO_PORTE_DATA_R & 0x0F;

        /* ????:??=0;??????=1 */
        if (rows != 0)
        {
            for (row = 0; row < 4; row++)
            {
                if (rows & (1U << row))
                {
                    char key = keymap[row][col];

                    /* ??? */
                    while (GPIO_PORTE_DATA_R & (1U << row)) { }
                    Delay_ms(20);      // ??

                    /* ??????? */
                    GPIO_PORTD_DATA_R &= ~0x0F;

                    return key;
                }
            }
        }
    }

    GPIO_PORTD_DATA_R &= ~0x0F;
    return 0;
}

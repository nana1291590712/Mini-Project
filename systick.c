#include "systick.h"

/* SysTick registers */
#define SYST_CSR   (*((volatile uint32_t *)0xE000E010))
#define SYST_RVR   (*((volatile uint32_t *)0xE000E014))
#define SYST_CVR   (*((volatile uint32_t *)0xE000E018))

/*
 * ?? PIOSC / 4 = 4 MHz / 4 = 1 MHz
 * ? 1 tick = 1 us
 * ?? TM4C datasheet ??????????
 */

void SysTick_Init(void)
{
    SYST_CSR = 0;        // disable SysTick
    SYST_CVR = 0;        // clear current

    /*
     * CTRL bits:
     * bit0 ENABLE = 0(???)
     * bit1 TICKINT = 0(????)
     * bit2 CLKSOURCE = 0(PIOSC/4)
     */
    SYST_CSR = 0x00;
}

void SysTick_Delay_us(uint32_t us)
{
    if (us == 0) return;

    /* PIOSC/4 = 1 MHz ? 1 tick = 1 us */
    if (us > 0xFFFFFF) us = 0xFFFFFF;

    SYST_RVR = us - 1;
    SYST_CVR = 0;
    SYST_CSR |= 0x01;          // ENABLE

    while ((SYST_CSR & (1 << 16)) == 0) { }

    SYST_CSR &= ~0x01;         // DISABLE
}

void SysTick_Delay_ms(uint32_t ms)
{
    while (ms--)
    {
        SysTick_Delay_us(1000);
    }
}

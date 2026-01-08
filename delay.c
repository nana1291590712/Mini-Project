#include "delay.h"
#include "systick.h"

/* Delay wrapper based on SysTick microsecond delay */
void Delay_us(uint32_t us)
{
    SysTick_Delay_us(us);
}

/* Delay wrapper based on SysTick millisecond delay */
void Delay_ms(uint32_t ms)
{
    SysTick_Delay_ms(ms);
}

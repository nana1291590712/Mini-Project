#include "delay.h"
#include "systick.h"

void Delay_us(uint32_t us)
{
    SysTick_Delay_us(us);
}

void Delay_ms(uint32_t ms)
{
    SysTick_Delay_ms(ms);
}

#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

/* Generate a blocking delay in microseconds */
void Delay_us(uint32_t us);

/* Generate a blocking delay in milliseconds */
void Delay_ms(uint32_t ms);

#endif

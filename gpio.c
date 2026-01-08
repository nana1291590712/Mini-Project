#include "gpio.h"

/* ================= Clock Control ================= */
/* Register used to enable clock for GPIO ports */
#define SYSCTL_RCGCGPIO_R   (*((volatile uint32_t *)0x400FE608))
/* Register used to check whether GPIO ports are ready */
#define SYSCTL_PRGPIO_R     (*((volatile uint32_t *)0x400FEA08))

/* ================= Port A ================= */
/* Base address of GPIO port A */
#define GPIO_PORTA_BASE     0x40004000
/* Register used to set direction of port A pins */
#define GPIO_PORTA_DIR_R    (*((volatile uint32_t *)(GPIO_PORTA_BASE + 0x400)))
/* Register used to enable digital function of port A pins */
#define GPIO_PORTA_DEN_R    (*((volatile uint32_t *)(GPIO_PORTA_BASE + 0x51C)))

/* ================= Port B ================= */
/* Base address of GPIO port B */
#define GPIO_PORTB_BASE     0x40005000
/* Register used to set direction of port B pins */
#define GPIO_PORTB_DIR_R    (*((volatile uint32_t *)(GPIO_PORTB_BASE + 0x400)))
/* Register used to enable digital function of port B pins */
#define GPIO_PORTB_DEN_R    (*((volatile uint32_t *)(GPIO_PORTB_BASE + 0x51C)))

/* ================= Port D ================= */
/* Base address of GPIO port D */
#define GPIO_PORTD_BASE     0x40007000
/* Register used to set direction of port D pins */
#define GPIO_PORTD_DIR_R    (*((volatile uint32_t *)(GPIO_PORTD_BASE + 0x400)))
/* Register used to enable digital function of port D pins */
#define GPIO_PORTD_DEN_R    (*((volatile uint32_t *)(GPIO_PORTD_BASE + 0x51C)))
/* Register used to unlock protected pins of port D */
#define GPIO_PORTD_LOCK_R   (*((volatile uint32_t *)(GPIO_PORTD_BASE + 0x520)))
/* Register used to allow configuration changes on port D pins */
#define GPIO_PORTD_CR_R     (*((volatile uint32_t *)(GPIO_PORTD_BASE + 0x524)))

/* ================= Port E ================= */
/* Base address of GPIO port E */
#define GPIO_PORTE_BASE     0x40024000
/* Register used to set direction of port E pins */
#define GPIO_PORTE_DIR_R    (*((volatile uint32_t *)(GPIO_PORTE_BASE + 0x400)))
/* Register used to enable digital function of port E pins */
#define GPIO_PORTE_DEN_R    (*((volatile uint32_t *)(GPIO_PORTE_BASE + 0x51C)))
/* Register used to enable pull down resistors on port E pins */
#define GPIO_PORTE_PDR_R    (*((volatile uint32_t *)(GPIO_PORTE_BASE + 0x514)))

void GPIO_Init(void)
{
    /* Enable clock for GPIO ports A B D and E */
    SYSCTL_RCGCGPIO_R |= 0x1B;
    /* Wait until all enabled GPIO ports are ready */
    while ((SYSCTL_PRGPIO_R & 0x1B) != 0x1B);

    /* Configure port A pins as outputs for LCD control */
    GPIO_PORTA_DIR_R |= 0x1C;
    GPIO_PORTA_DEN_R |= 0x1C;

    /* Configure port B pins as outputs for LCD data */
    GPIO_PORTB_DIR_R = 0xFF;
    GPIO_PORTB_DEN_R = 0xFF;

    /* Configure port D pins as outputs for keypad columns */
    GPIO_PORTD_LOCK_R = 0x4C4F434B;
    GPIO_PORTD_CR_R  |= 0x0F;
    GPIO_PORTD_DIR_R |= 0x0F;
    GPIO_PORTD_DEN_R |= 0x0F;

    /* Configure port E pins as inputs for keypad rows */
    GPIO_PORTE_DIR_R &= ~0x0F;
    GPIO_PORTE_DEN_R |=  0x0F;
    GPIO_PORTE_PDR_R |=  0x0F;
}

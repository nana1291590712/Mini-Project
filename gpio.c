#include "gpio.h"

/* ================= Clock Control ================= */
#define SYSCTL_RCGCGPIO_R   (*((volatile uint32_t *)0x400FE608))
#define SYSCTL_PRGPIO_R     (*((volatile uint32_t *)0x400FEA08))

/* ================= Port A (LCD Control) ================= */
#define GPIO_PORTA_BASE     0x40004000
#define GPIO_PORTA_DIR_R    (*((volatile uint32_t *)(GPIO_PORTA_BASE + 0x400)))
#define GPIO_PORTA_DEN_R    (*((volatile uint32_t *)(GPIO_PORTA_BASE + 0x51C)))

/* ================= Port B (LCD Data) ================= */
#define GPIO_PORTB_BASE     0x40005000
#define GPIO_PORTB_DIR_R    (*((volatile uint32_t *)(GPIO_PORTB_BASE + 0x400)))
#define GPIO_PORTB_DEN_R    (*((volatile uint32_t *)(GPIO_PORTB_BASE + 0x51C)))

/* ================= Port D (Keypad Columns) ================= */
#define GPIO_PORTD_BASE     0x40007000
#define GPIO_PORTD_DIR_R    (*((volatile uint32_t *)(GPIO_PORTD_BASE + 0x400)))
#define GPIO_PORTD_DEN_R    (*((volatile uint32_t *)(GPIO_PORTD_BASE + 0x51C)))
#define GPIO_PORTD_LOCK_R   (*((volatile uint32_t *)(GPIO_PORTD_BASE + 0x520)))
#define GPIO_PORTD_CR_R     (*((volatile uint32_t *)(GPIO_PORTD_BASE + 0x524)))

/* ================= Port E (Keypad Rows) ================= */
#define GPIO_PORTE_BASE     0x40024000
#define GPIO_PORTE_DIR_R    (*((volatile uint32_t *)(GPIO_PORTE_BASE + 0x400)))
#define GPIO_PORTE_DEN_R    (*((volatile uint32_t *)(GPIO_PORTE_BASE + 0x51C)))
#define GPIO_PORTE_PDR_R    (*((volatile uint32_t *)(GPIO_PORTE_BASE + 0x514)))  // ???

void GPIO_Init(void)
{
    /* Enable clock for A, B, D, E */
    SYSCTL_RCGCGPIO_R |= 0x1B;
    while ((SYSCTL_PRGPIO_R & 0x1B) != 0x1B);

    /* LCD: PA2-PA4 */
    GPIO_PORTA_DIR_R |= 0x1C;
    GPIO_PORTA_DEN_R |= 0x1C;

    /* LCD: PB0-PB7 */
    GPIO_PORTB_DIR_R = 0xFF;
    GPIO_PORTB_DEN_R = 0xFF;

    /* Keypad columns: PD0-PD3 output */
    GPIO_PORTD_LOCK_R = 0x4C4F434B;
    GPIO_PORTD_CR_R  |= 0x0F;
    GPIO_PORTD_DIR_R |= 0x0F;
    GPIO_PORTD_DEN_R |= 0x0F;

    /* Keypad rows: PE0-PE3 input + pull-down */
    GPIO_PORTE_DIR_R &= ~0x0F;
    GPIO_PORTE_DEN_R |=  0x0F;
    GPIO_PORTE_PDR_R |=  0x0F;   // ???:??????
}

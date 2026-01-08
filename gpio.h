#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/* Initialize all GPIO ports used in the system:
 * - Port A/B for LCD
 * - Port D/E for keypad
 */
void GPIO_Init(void);

#endif  
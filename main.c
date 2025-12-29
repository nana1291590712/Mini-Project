#include <stdio.h>

#include "gpio.h"
#include "lcd.h"
#include "keypad.h"
#include "delay.h"
#include "input.h"
#include "calc.h"

int main(void)
{
    char key;
    double result;
    char buf[17];

    GPIO_Init();
    LCD_Init();
    Input_Init();

    LCD_SetCursor(0,0);
    LCD_PrintString("Calculator");

    LCD_SetCursor(1,0);
    LCD_PrintString("                ");

    while (1)
    {
        key = Keypad_GetKey();
        if (!key) continue;

        /* '=' ??? '*' ?? */
        if (key == '*')
        {
            result = calc_eval(Input_GetExpr());

            snprintf(buf, 17, "%.8g", result);

            /* ?????,???????(?????) */
            Input_SetExpr(buf);

            LCD_SetCursor(1,0);
            LCD_PrintString("                ");
            LCD_SetCursor(1,0);
            LCD_PrintString(buf);

            Delay_ms(300);
            continue;
        }

        /* ?????????? */
        Input_HandleKey(key);

        LCD_SetCursor(1,0);
        LCD_PrintString("                ");
        LCD_SetCursor(1,0);
        LCD_PrintString(Input_GetExpr());

        Delay_ms(120);
    }
}

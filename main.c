#include <stdio.h>

#include "gpio.h"
#include "lcd.h"
#include "keypad.h"
#include "delay.h"
#include "input.h"
#include "calc.h"

/* Display shift status text on the first row of the LCD */
static void LCD_ShowShift(void)
{
    /* Move cursor to fixed position on the first row */
    LCD_SetCursor(0, 11);
    LCD_PrintString("SHIFT");
}

/* Clear shift status text from the LCD */
static void LCD_ClearShift(void)
{
    /* Overwrite shift area with blank spaces */
    LCD_SetCursor(0, 11);
    LCD_PrintString("     ");
}

int main(void)
{
    char key;
    double result;
    char buf[17];

    /* Initialize hardware modules */
    GPIO_Init();
    LCD_Init();
    Input_Init();

    /* Display calculator title */
    LCD_SetCursor(0,0);
    LCD_PrintString("Calculator");

    /* Clear second line */
    LCD_SetCursor(1,0);
    LCD_PrintString("                ");

    /* Ensure shift indicator is cleared at startup */
    LCD_ClearShift();

    while (1)
    {
        /* Read keypad input */
        key = Keypad_GetKey();
        if (!key) continue;

        /* Execute calculation when result key is pressed */
        if (key == '*')
        {
            /* Ignore evaluation if input is in error state */
            if (Input_HasError())
            {
                Delay_ms(200);
                continue;
            }

            /* Evaluate expression and format result */
            result = calc_eval(Input_GetExpr());
            snprintf(buf, 17, "%.8g", result);

            /* Replace current expression with result */
            Input_SetExpr(buf);

            /* Update LCD with calculation result */
            LCD_SetCursor(1,0);
            LCD_PrintString("                ");
            LCD_SetCursor(1,0);
            LCD_PrintString(buf);

            /* Update shift indicator based on current mode */
            if (Input_IsShift()) LCD_ShowShift();
            else LCD_ClearShift();

            Delay_ms(300);
            continue;
        }

        /* Handle normal key input */
        Input_HandleKey(key);

        /* Refresh second line display */
        LCD_SetCursor(1,0);
        LCD_PrintString("                ");
        LCD_SetCursor(1,0);

        /* Display error message or current expression */
        if (Input_HasError())
            LCD_PrintString("Error");
        else
            LCD_PrintString(Input_GetExpr());

        /* Update shift indicator on the first row */
        if (Input_IsShift())
            LCD_ShowShift();
        else
            LCD_ClearShift();

        Delay_ms(120);
    }
}

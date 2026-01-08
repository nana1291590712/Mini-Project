#include "input.h"
#include <string.h>

/* Expression buffer */
static char expr[MAX_LEN + 1];
static int pos;

/* Shift mode state */
static int shift_mode;

/* Error state flag */
static int error_flag;

/* ------------------------------------------------ */
/* Check whether a character is an operator */
static int is_op(char c)
{
    return (c == '+' || c == '-' || c == 'x' || c == '/');
}

/* Initialize input module state */
void Input_Init(void)
{
    memset(expr, 0, sizeof(expr));
    pos = 0;
    shift_mode = 0;
    error_flag = 0;
}

/* Return current expression string */
const char *Input_GetExpr(void)
{
    return expr;
}

/* Replace expression with given string */
void Input_SetExpr(const char *s)
{
    int i = 0;
    pos = 0;
    error_flag = 0;

    while (s[i] && pos < MAX_LEN)
    {
        expr[pos++] = s[i++];
    }
    expr[pos] = '\0';
}

/* ------------------------------------------------ */
/* Append a character to expression */
static void append_char(char c)
{
    if (pos < MAX_LEN)
    {
        expr[pos++] = c;
        expr[pos] = '\0';
    }
}

/* Append operator and check for invalid sequence */
static void append_op(char op)
{
    if (pos > 0 && is_op(expr[pos - 1]))
    {
        error_flag = 1;
        return;
    }
    append_char(op);
}

/* Remove last character from expression */
static void backspace(void)
{
    if (pos > 0)
    {
        pos--;
        expr[pos] = '\0';

        if (pos < 2 || !is_op(expr[pos - 1]) || !is_op(expr[pos - 2]))
        {
            error_flag = 0;
        }
    }
}

/* Clear entire expression buffer */
static void clear_all(void)
{
    pos = 0;
    expr[0] = '\0';
    error_flag = 0;
}

/* ------------------------------------------------ */
/* Handle keypad input according to current mode */
void Input_HandleKey(char key)
{
    /* Toggle shift mode */
    if (key == 'D')
    {
        shift_mode = !shift_mode;
        return;
    }

    /* Handle numeric input */
    if (key >= '0' && key <= '9')
    {
        append_char(key);
        return;
    }

    /* Handle keys in normal mode */
    if (!shift_mode)
    {
        if      (key == 'A') append_op('+');
        else if (key == 'B') append_op('-');
        else if (key == 'C') append_char('.');
        else if (key == '#') backspace();
    }
    /* Handle keys in shift mode */
    else
    {
        if      (key == 'A') append_op('x');
        else if (key == 'B') append_op('/');
        else if (key == '#') clear_all();
    }
}

/* ------------------------------------------------ */
/* Return error state */
int Input_HasError(void)
{
    return error_flag;
}

/* Clear error state */
void Input_ClearError(void)
{
    error_flag = 0;
}

/* Return shift mode state */
int Input_IsShift(void)
{
    return shift_mode;
}

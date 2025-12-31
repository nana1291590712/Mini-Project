#include "input.h"
#include <string.h>

/* ????? */
static char expr[MAX_LEN + 1];
static int pos;

/* Shift ??:0 = normal, 1 = shift */
static int shift_mode;

/* Error ?? */
static int error_flag;

/* ------------------------------------------------ */
static int is_op(char c)
{
    return (c == '+' || c == '-' || c == 'x' || c == '/');
}

void Input_Init(void)
{
    memset(expr, 0, sizeof(expr));
    pos = 0;
    shift_mode = 0;
    error_flag = 0;
}

const char *Input_GetExpr(void)
{
    return expr;
}

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
static void append_char(char c)
{
    if (pos < MAX_LEN)
    {
        expr[pos++] = c;
        expr[pos] = '\0';
    }
}

static void append_op(char op)
{
    if (pos > 0 && is_op(expr[pos - 1]))
    {
        error_flag = 1;
        return;
    }
    append_char(op);
}

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

static void clear_all(void)
{
    pos = 0;
    expr[0] = '\0';
    error_flag = 0;
}

/* ------------------------------------------------ */
void Input_HandleKey(char key)
{
    /* Shift ?? */
    if (key == 'D')
    {
        shift_mode = !shift_mode;
        return;
    }

    /* ?? */
    if (key >= '0' && key <= '9')
    {
        append_char(key);
        return;
    }

    /* Normal ?? */
    if (!shift_mode)
    {
        if      (key == 'A') append_op('+');
        else if (key == 'B') append_op('-');
        else if (key == 'C') append_char('.');
        else if (key == '#') backspace();
    }
    /* Shift ?? */
    else
    {
        if      (key == 'A') append_op('x');
        else if (key == 'B') append_op('/');
        else if (key == '#') clear_all();
    }
}

/* ------------------------------------------------ */
int Input_HasError(void)
{
    return error_flag;
}

void Input_ClearError(void)
{
    error_flag = 0;
}

int Input_IsShift(void)
{
    return shift_mode;
}

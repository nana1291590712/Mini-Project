#include "calc.h"

/* ??????(????) */
static double parse_number(const char *s, int *i)
{
    double v = 0.0;
    double frac = 0.0;
    double base = 0.1;
    int dot = 0;

    while ((s[*i] >= '0' && s[*i] <= '9') || s[*i] == '.')
    {
        if (s[*i] == '.')
        {
            dot = 1;
        }
        else if (!dot)
        {
            v = v * 10 + (s[*i] - '0');
        }
        else
        {
            frac += (s[*i] - '0') * base;
            base *= 0.1;
        }
        (*i)++;
    }
    return v + frac;
}

/* ?????? */
static int precedence(char op)
{
    if (op == '+' || op == '-') return 1;
    if (op == 'x' || op == '/') return 2;
    return 0;
}

/* ?????? */
static double apply(double a, double b, char op)
{
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == 'x') return a * b;
    if (op == '/') return (b != 0) ? a / b : 0.0;
    return 0.0;
}

/* ======================
 * ??????(????)
 * ====================== */
double calc_eval(const char *expr)
{
    double numStack[16];
    char   opStack[16];
    int nTop = -1;
    int oTop = -1;
    int i = 0;

    while (expr[i])
    {
        /* ????? */
        numStack[++nTop] = parse_number(expr, &i);

        /* ????????? */
        if (expr[i])
        {
            char op = expr[i++];

            /* ????? */
            while (oTop >= 0 &&
                   precedence(opStack[oTop]) >= precedence(op))
            {
                double b = numStack[nTop--];
                double a = numStack[nTop--];
                numStack[++nTop] = apply(a, b, opStack[oTop--]);
            }

            opStack[++oTop] = op;
        }
    }

    /* ????????? */
    while (oTop >= 0)
    {
        double b = numStack[nTop--];
        double a = numStack[nTop--];
        numStack[++nTop] = apply(a, b, opStack[oTop--]);
    }

    return numStack[nTop];
}

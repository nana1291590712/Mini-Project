#include "calc.h"

/* Parse a numeric value from expression string */
static double parse_number(const char *s, int *i)
{
    double v = 0.0;
    double frac = 0.0;
    double base = 0.1;
    int dot = 0;

    /* Read integer and fractional parts */
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

/* Return operator precedence level */
static int precedence(char op)
{
    if (op == '+' || op == '-') return 1;
    if (op == 'x' || op == '/') return 2;
    return 0;
}

/* Apply arithmetic operation to two operands */
static double apply(double a, double b, char op)
{
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == 'x') return a * b;
    if (op == '/') return (b != 0) ? a / b : 0.0;
    return 0.0;
}

/* Evaluate expression using operator precedence */
double calc_eval(const char *expr)
{
    double numStack[16];
    char   opStack[16];
    int nTop = -1;
    int oTop = -1;
    int i = 0;

    /* Scan through expression string */
    while (expr[i])
    {
        /* Read next number and push to number stack */
        numStack[++nTop] = parse_number(expr, &i);

        /* Process operator if present */
        if (expr[i])
        {
            char op = expr[i++];

            /* Apply operators with higher or equal precedence */
            while (oTop >= 0 &&
                   precedence(opStack[oTop]) >= precedence(op))
            {
                double b = numStack[nTop--];
                double a = numStack[nTop--];
                numStack[++nTop] = apply(a, b, opStack[oTop--]);
            }

            /* Push current operator to operator stack */
            opStack[++oTop] = op;
        }
    }

    /* Apply remaining operators */
    while (oTop >= 0)
    {
        double b = numStack[nTop--];
        double a = numStack[nTop--];
        numStack[++nTop] = apply(a, b, opStack[oTop--]);
    }

    return numStack[nTop];
}

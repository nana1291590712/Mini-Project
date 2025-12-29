#include "calc.h"
#include <stdlib.h>

double calc_eval(const char *s)
{
    double result = 0.0;
    double value = 0.0;
    char op = 0;
    int i = 0;

    /* ???? */
    result = atof(s);

    /* ??????? */
    while ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') i++;

    while (s[i] != '\0')
    {
        op = s[i++];
        value = atof(&s[i]);

        while ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') i++;

        if (op == '+') result += value;
        else if (op == '-') result -= value;
        else if (op == 'x') result *= value;
        else if (op == '/') result /= value;
    }

    return result;
}

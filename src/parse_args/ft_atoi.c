#include "../include/codexion.h"


long ft_atoi(char *string_number)
{
    int i;
    long res;

    i = 0;
    res = 0;
    if (string_number[i] == '-')
        return (-1);
    if (string_number[i] == '+')
        i++;
    while (string_number[i] != '\0')
    {
        if (res > (INT_MAX - (string_number[i] - '0')) / 10)
            return (-1);
        res = 10 * res + (string_number[i] - '0');
        i++;
    }
    return (res);
}
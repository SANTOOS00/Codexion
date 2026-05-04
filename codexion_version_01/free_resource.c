#include "codexion.h"

void ft_free_resource(void **args, int cont)
{
    int i;

    i = 0;
    while(i < cont)
        free(args[i++]);
    free(args);
}

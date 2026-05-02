#include "codexion.h"

t_dongle *initialize_dongles(int number_of_coders)
{
    static t_dongle *dongles;
    
    if (dongles == NULL)
    {
        dongles = malloc(sizeof(t_dongle) * number_of_coders);
        if (!dongles)
            return (free_source(fail_coders, number_of_coders), NULL);
    }
    return dongles;
}
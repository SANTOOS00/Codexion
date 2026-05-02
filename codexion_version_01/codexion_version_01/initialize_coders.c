#include "codexion.h"




void free_coders(int i, t_coder **coders)
{
    while (i)
    {
        free(coders[i]);
        i--;
    }
}



t_action initialize(int number_of_coders, t_coder **coders)
{
    int i;
    pthread_mutex_t *mutex;

    i = 0;
    mutex = malloc(sizeof(pthread_mutex_t));
    if (!mutex)
        return fail;
    while (i < number_of_coders)
    {
        coders[i] = malloc(sizeof(t_coder));
        if (!coders[i])
            return (free_coders(i, coders), fail);
        coders[i]->mutex = mutex;
        i++;
    }
    return success;
}
t_coder **initialize_coders(int number_of_coders)
{
    static t_coder **coders;
    
    if (coders == NULL)
    {
        coders = malloc(sizeof(t_coder **) * number_of_coders);
        if (!coders)
            return (NULL);
        if (initialize(number_of_coders, coders) == fail)
            return (NULL);
    }
    return coders;
}
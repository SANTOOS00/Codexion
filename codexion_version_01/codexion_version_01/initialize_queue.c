#include "codexion.h"

static void free_coders(int i, t_queue **queue)
{
    while (i)
    {
        free(queue[i]);
        i--;
    }
}

static t_action initialize(int number_of_coders, t_queue **queue)
{
    int i;
    pthread_mutex_t *mutex;

    i = 0;
    mutex = malloc(sizeof(pthread_mutex_t));
    if (!mutex)
        return fail;
    while (i < number_of_coders)
    {
        queue[i] = malloc(sizeof(t_coder));
        if (!queue[i])
            return (free_coders(i, queue), fail);
        queue[i]->mutex = mutex;
        i++;
    }
    return success;
}


t_queue **initialize_queue(int number_of_coders)
{
    static t_queue **queue;
    
    if (queue == NULL)
    {
        queue = malloc(sizeof(t_queue **));
        if (!queue)
            return (free_source(fail_queue, number_of_coders), NULL);
        if (initialize(number_of_coders, queue) == fail)
            return (free_source(fail_queue, number_of_coders), NULL);
    }
    return queue;
}
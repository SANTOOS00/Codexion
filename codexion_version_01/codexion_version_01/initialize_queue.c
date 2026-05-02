#include "codexion.h"

static void free_coders(int i, t_queue **queue)
{
    while (i)
    {
        i--;
        free(queue[i]);
    }
    free(queue);
}

static t_action initialize(int number_of_coders, t_queue **queue)
{
    int i = 0;
    pthread_mutex_t *mutex;

    mutex = malloc(sizeof(pthread_mutex_t));
    if (!mutex)
        return fail;

    pthread_mutex_init(mutex, NULL);

    while (i < number_of_coders)
    {
        queue[i] = malloc(sizeof(t_queue));
        if (!queue[i])
        {
            free_coders(i, queue);
            pthread_mutex_destroy(mutex);
            free(mutex);
            return fail;
        }
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
        queue = malloc(sizeof(t_queue *) * number_of_coders);
        if (!queue)
            return (free_source(fail_queue, number_of_coders), NULL);
        if (initialize(number_of_coders, queue) == fail)
            return (free_source(fail_queue, number_of_coders), NULL);
    }
    return queue;
}
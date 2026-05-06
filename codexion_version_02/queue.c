#include "codexion.h"





void clean_queue(t_queue *queue)
{
    free_2d_array((void **)queue->coders, queue->max_size);
    free(queue);
}


bool ft_init_queue(t_simulation *sim)
{
    t_queue *queue;

    queue = (t_queue *)malloc(sizeof(t_queue));
    if (!queue)
        return(false);
    queue->coders = alloc_coders(sim->config.number_of_coders);
    if(!queue->coders)
        return (free(queue), false);
    queue->max_size = sim->config.number_of_coders;
    sim->queue = queue;
    return (true);
}
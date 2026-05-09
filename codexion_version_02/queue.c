#include "codexion.h"





void clean_queue(t_queue *queue)
{
    int i;

    i = 0;
    pthread_mutex_destroy(&queue->mutex);
    while (i < queue->capacity)
        free(queue->heap[i++]);
    free(queue->heap);
    free(queue);
}


void print_queue(t_queue *queue)
{
    int i;
    i = 0;
    while (i < queue->capacity)
    {
        pthread_mutex_lock(&queue->mutex);
        printf("id -> %d index %d  || %d  %d\n", queue->heap[i]->coder->id, queue->heap[i]->index_coder, queue->heap[i]->coder->left_dongle->is_available, queue->heap[i]->coder->right_dongle->is_available);
        pthread_mutex_unlock(&queue->mutex);
        i++;
    }
}

bool ft_init_queue(t_simulation *sim)
{
    t_queue *queue;
    int i;
    int j;

    j = 0;
    i = 0;
    queue = (t_queue *)malloc(sizeof(t_queue));
    if (!queue)
        return (false);
    if (pthread_mutex_init(&queue->mutex, NULL) != 0)
        return (free(queue), false);
    queue->heap = (t_dongle_request **)malloc(sizeof(t_dongle_request) *sim->config.number_of_coders);
    if (!queue->heap)
        return (free(queue) , false);
    while (i < sim->config.number_of_coders)
    {
        queue->heap[i] = (t_dongle_request *)malloc(sizeof(t_dongle_request));
        if (!queue->heap[i])
        {
            while (j < i)
                free(queue->heap[j++]);
            free(queue->heap);
            free(queue);
            return (false);
        }
        i++;
    }
    queue->capacity = sim->config.number_of_coders;
    queue->size = 0;
    sim->queue = queue;
    i = 0;
    while (i < queue->capacity)
        sim->coders[i++]->queue = queue;
    return (true);
}
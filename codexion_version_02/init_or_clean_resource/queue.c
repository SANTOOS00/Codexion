/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:24:44 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/12 15:23:35 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../codexion.h"

void clean_queue(t_queue *queue)
{
    int i;

    i = 0;
    pthread_mutex_destroy(&queue->mutex_queue);
    while (i < queue->capacity)
        free(queue->heap[i++]);
    free(queue->heap);
    free(queue);
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
    if (pthread_mutex_init(&queue->mutex_queue, NULL) != 0)
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
    return (true);
}

// void print_queue(t_queue *queue)
// {
//     int i;
//     i = 0;
//     while (i < queue->size)
//     {
//         pthread_mutex_lock(&queue->mutex_queue_priority);
//         pthread_mutex_lock(&queue->heap[i]->coder->right_dongle->m_cn_dongle.mutex);
        
//         printf("id -> %d index %d  time %lld|| %d  %d   left index %d, right index %d\n", 
//             queue->heap[i]->coder->id,
//             queue->heap[i]->coder->index_in_queue,
//             queue->heap[i]->deadline,
//             queue->heap[i]->coder->left_dongle->is_available, 
//             queue->heap[i]->coder->right_dongle->is_available,
//             *(queue->heap[i]->coder->index_coder_right_queue),
//             *(queue->heap[i]->coder->index_coder_left_queue));
//         pthread_mutex_unlock(&queue->mutex_queue_priority);
//         pthread_mutex_unlock(&queue->heap[i]->coder->right_dongle->m_cn_dongle.mutex);
//         i++;
//     }
// }

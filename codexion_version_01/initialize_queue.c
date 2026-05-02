/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_queue.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 16:54:31 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/02 18:40:55 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    int i;
    pthread_mutex_t *mutex;

    mutex = malloc(sizeof(pthread_mutex_t));
    if (!mutex)
        return fail;
    pthread_mutex_init(mutex, NULL);
    i = 0;
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
        queue[i]->index_coder = -1;
        i++;
        if (i == number_of_coders)
            queue[number_of_coders] = NULL;
    }
    return success;
}


t_queue **initialize_queue(int number_of_coders)
{
    static t_queue **queue = NULL;
    
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
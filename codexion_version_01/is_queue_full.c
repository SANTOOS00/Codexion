/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_queue_full.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 18:37:02 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/02 19:07:12 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "codexion.h"

t_queue_state is_queue_fully_populated(int number_of_coders)
{
    t_queue **queue;
    int i;

    i = 0;
    queue = initialize_queue(0);
    while (i < number_of_coders)
    {
        pthread_mutex_lock(queue[0]->mutex);
        if (queue[i]->index_coder == -1)
            return (pthread_mutex_unlock(queue[0]->mutex), QUEUE_INCOMPLETE);
        pthread_mutex_unlock(queue[0]->mutex);
        i++;
    }
    return (QUEUE_COMPLETE);
}

void is_queue_full(int number_of_coders)
{
    while (is_queue_fully_populated(number_of_coders) == QUEUE_INCOMPLETE);
}
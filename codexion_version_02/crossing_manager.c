/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crossing_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 16:15:36 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/12 18:16:36 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder *pop_crossing(t_coder_crossing *cro)
{
    t_coder *coder;
    int i;

    coder = cro->heap[0];
    if (cro->size == 1)
    {
        cro->size--;
        return (coder);   
    }
    i = 1;
    while (cro->size > i)
    {
        cro->heap[i - 1] = cro->heap[i];
        i++;
    }
    cro->size--;
    return (coder);
}




void add_crossing_to_queue(t_coder_crossing *cro, t_queue *q, t_scheduler scheduler)
{
    t_coder *coder;

    pthread_mutex_lock(&cro->mutex_crossing);
    while (cro->size > 0)
    {
        coder = pop_crossing(cro);
        printf("%d\n", coder->id);
        pthread_mutex_lock(&q->mutex_queue);
        push_to_priority_queue(q, coder, scheduler);
        pthread_mutex_unlock(&q->mutex_queue);
        
    }
    pthread_mutex_unlock(&cro->mutex_crossing);
}



void push_crossing(t_coder *coder)
{
    t_coder_crossing *crossing;
    
    crossing = coder->crossing;
    pthread_mutex_lock(&crossing->mutex_crossing);
    crossing->heap[crossing->size] = coder;
    crossing->size++;
    pthread_mutex_unlock(&crossing->mutex_crossing);
}
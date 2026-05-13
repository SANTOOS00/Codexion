/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crossing_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 16:15:36 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/12 20:39:10 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder *pop_crossing(t_coder_crossing *cro)
{
    t_coder *coder;
    int i;

    coder = cro->heap[0];
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

    while (cro->size > 0)
    {
        coder = pop_crossing(cro);
        push_to_priority_queue(q, coder, scheduler);        
    }
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
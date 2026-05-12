/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 17:20:51 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/12 18:17:29 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



int parent_index(int index)
{
    return (index - 1) / 2;
}

void ft_swap(t_dongle_request **s1, t_dongle_request **s2)
{
    t_dongle_request *temp;

    temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}


bool is_greater(t_dongle_request *req1, t_dongle_request *req2)
{
    return (req1->deadline < req2->deadline);
}


void heapify_up(t_queue *q, int index)
{
    int parent;
    
    while (index > 0)
    {
        parent = parent_index(index);
        if (is_greater(q->heap[index], q->heap[parent]))
        {
            ft_swap(&q->heap[index], &q->heap[parent]);
            index = parent;
        }
        else
            break;
    }
}

void push_to_priority_queue(t_queue *q, t_coder *coder, t_scheduler scheduler)
{
    
    
    q->heap[q->size]->coder = coder;
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    if(coder->status == START)
        q->heap[q->size]->deadline = get_time();
    pthread_mutex_unlock(&coder->mutex_cond.mutex);    
    if (scheduler == EDF)
        heapify_up(q, q->size);
    printf("size queue %d\n", q->heap[q->size]->coder->id);
    q->size++;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 17:20:51 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/12 20:11:16 by moerrais         ###   ########.fr       */
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

// static t_dongle_request *init_queue(t_coder *coder, t_queue *q)
// {
//     t_dongle_request *req;
//     long long time;

//     time =  q->time_burnout + get_time();
//     coder->deadline = time;
//     req->coder = coder;
//     req->deadline = time;
//     return (req);
// }


// void push_to_priority_queue(t_queue *q, t_coder *coder, t_scheduler scheduler)
// {
        
//     q->heap[q->size]->coder = coder;
//     pthread_mutex_lock(&coder->mutex_cond.mutex);
//     if(coder->status == START)
//     {
//         q->heap[q->size]->coder->deadline = get_time();
//         q->heap[q->size]->deadline = coder->deadline;
//     }
//     pthread_mutex_unlock(&coder->mutex_cond.mutex);    
//     if (scheduler == EDF)
//         heapify_up(q, q->size);
//     q->size++;
// }

void push_to_priority_queue(t_queue *q, t_coder *coder, t_scheduler scheduler)
{
    pthread_mutex_lock(&q->mutex_queue);
    
    if (q->size >= q->capacity)
    {
        pthread_mutex_unlock(&q->mutex_queue);
        return;
    }

    q->heap[q->size]->coder = coder;
    
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    if(coder->status == START)
    {
        coder->deadline = get_time();
        q->heap[q->size]->deadline = coder->deadline;
    }
    pthread_mutex_unlock(&coder->mutex_cond.mutex);    

    if (scheduler == EDF)
        heapify_up(q, q->size);
    q->size++;
    pthread_mutex_unlock(&q->mutex_queue);
}


bool is_dongle_left(t_dongle *dongle)
{
    bool is_valid;

    pthread_mutex_lock(&dongle->m_cn_dongle.mutex);
    is_valid = dongle->is_available;
    pthread_mutex_unlock(&dongle->m_cn_dongle.mutex);
    return (is_valid);
}

bool is_dongle_right(t_dongle *dongle)
{
    bool is_valid;

    pthread_mutex_lock(&dongle->m_cn_dongle.mutex);
    is_valid = dongle->is_available;
    pthread_mutex_unlock(&dongle->m_cn_dongle.mutex);
    return (is_valid);
}

bool is_valid_dongl_left_right(t_coder *coder)
{
    return (is_dongle_left(coder->left_dongle) && is_dongle_right(coder->right_dongle));
}

t_coder *pop_queue(t_queue *q, t_scheduler scheduler)
{
    t_coder *coder = NULL;
    int i = 1;

    pthread_mutex_lock(&q->mutex_queue);
    if (q->size == 0) {
        pthread_mutex_unlock(&q->mutex_queue);
        return (NULL);
    }

    if (scheduler == FIFO && is_valid_dongl_left_right(q->heap[0]->coder))
    {
        coder = q->heap[0]->coder;
        pick_up_dongle(coder);
        while (i < q->size) {
            q->heap[i - 1]->coder = q->heap[i]->coder;
            q->heap[i - 1]->deadline = q->heap[i]->deadline;
            i++;
        }
        q->size--;
    }

    pthread_mutex_unlock(&q->mutex_queue);
    return (coder);
}
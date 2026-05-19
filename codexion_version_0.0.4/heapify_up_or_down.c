/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heapify_up_or_down.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 14:26:27 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/16 14:26:36 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int parent_index(int index)
{
    return (index - 1) / 2;
}

int cheld_left_index(int index)
{
    return ((2 * index) + 1);
}

int cheld_right_index(int index)
{
    return ((2 * index) + 2);
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

void heapify_down(t_queue *q, int parent)
{
    int cheld_left;
    int cheld_right;
    int index;

    index = parent;
    while (parent < q->size)
    {
        cheld_left = cheld_left_index(parent);
        cheld_right = cheld_right_index(parent);
        if (cheld_left < q->size && is_greater(q->heap[parent], q->heap[cheld_left]))
            index = cheld_left;
        if (cheld_right < q->size && is_greater(q->heap[parent], q->heap[cheld_right]))
            index = cheld_right;
        if (index == parent)
            break;
        ft_swap(&q->heap[index], &q->heap[parent]);
        parent = index;
    }
}
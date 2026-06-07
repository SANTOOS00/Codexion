/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heapify_up_or_down.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 14:26:27 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/06 03:49:47 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	ft_swap(t_dongle_request **s1, t_dongle_request **s2)
{
	t_dongle_request	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void	heapify_up(t_queue *q, int index)
{
	int	parent;

	while (index > 0)
	{
		parent = parent_index(index);
		if (is_greater(q->heap[index], q->heap[parent]))
		{
			ft_swap(&q->heap[index], &q->heap[parent]);
			index = parent;
		}
		else if (is_same_deadline(q->heap[index], q->heap[parent])
			&& q->heap[index]->coder->id < q->heap[parent]->coder->id)
		{
			ft_swap(&q->heap[index], &q->heap[parent]);
			index = parent;
		}
		else
			break ;
	}
}

void	heapify_down(t_queue *q, int parent)
{
	int	cheld_left;
	int	cheld_right;
	int	index;

	while (parent < q->size)
	{
		cheld_left = cheld_left_index(parent);
		cheld_right = cheld_right_index(parent);
		index = parent;
		if (cheld_left < q->size && is_greater(q->heap[cheld_left],
				q->heap[parent]))
			index = cheld_left;
		if (cheld_right < q->size && is_greater(q->heap[cheld_right],
				q->heap[cheld_right]))
			index = cheld_right;
		if (index == parent)
			break ;
		ft_swap(&q->heap[index], &q->heap[parent]);
		parent = index;
	}
}

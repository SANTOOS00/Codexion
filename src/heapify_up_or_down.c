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

bool test_name_com(t_dongle_request *req1, t_dongle_request *req2)
{
	bool test = false;
	pthread_mutex_lock(&req1->coder->mutex_cond.mutex);
	pthread_mutex_lock(&req2->coder->mutex_cond.mutex);
	if (req1->coder->compilation_count < req2->coder->compilation_count)
	{
		test = true;
	}	
	pthread_mutex_unlock(&req1->coder->mutex_cond.mutex);
	pthread_mutex_unlock(&req2->coder->mutex_cond.mutex);
	return (test);
}

void	heapify_up(t_queue *q, int index)
{
	int	parent;

	while (index > 0)
	{
		parent = parent_index(index);
		if (test_name_com(q->heap[index], q->heap[parent]) || is_greater(q->heap[index], q->heap[parent]))
		{
			ft_swap(&q->heap[index], &q->heap[parent]);
			index = parent;
		}	
		else
			break ;
	}
}



int		heapify_down(t_queue *q, int parent)
{
	int	cheld_left;
	int	cheld_right;
	int	index;

	index = parent;
	while (parent < q->size)
	{
		cheld_left = cheld_left_index(parent);
		cheld_right = cheld_right_index(parent);
		index = parent;
		if (cheld_left < q->size && (is_greater(q->heap[cheld_left], q->heap[parent]) || test_name_com(q->heap[cheld_left],q->heap[parent])))
			index = cheld_left;
		if (cheld_right < q->size && (is_greater(q->heap[cheld_right], q->heap[parent]) || test_name_com(q->heap[cheld_right],q->heap[parent])))
			index = cheld_right;
		if (index == parent)
			break ;
		ft_swap(&q->heap[index], &q->heap[parent]);
		parent = index;
	}
	return (index);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_edf_or_fifo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:16:29 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/06 03:44:46 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	push_to_priority_queue(t_queue *q, t_coder *coder,
		t_scheduler scheduler)
{
	pthread_mutex_lock(&q->mutex_queue);
	if (q->size >= q->capacity)
	{
		pthread_mutex_unlock(&q->mutex_queue);
		return ;
	}
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	q->heap[q->size]->coder = coder;
	q->heap[q->size]->deadline = coder->deadline;
	if (coder->status == START)
	{
		coder->deadline = q->time_burnout + get_time();
		q->heap[q->size]->deadline = coder->deadline;
	}
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
	if (scheduler == EDF)
	{
		heapify_down(q, q->size);
		heapify_up(q, q->size);
	}
	q->size++;
	pthread_mutex_unlock(&q->mutex_queue);
}

bool	is_valid_dongl_left_right(t_coder *coder)
{
	return (try_take_dongle(coder->left_dongle)
		&& try_take_dongle(coder->right_dongle));
}

void	shift_queue_elements(t_queue *q)
{
	int	i;

	i = 1;
	while (i < q->size)
	{
		q->heap[i - 1]->coder = q->heap[i]->coder;
		q->heap[i - 1]->deadline = q->heap[i]->deadline;
		i++;
	}
}

t_coder	*pop_highest_priority_ready_coder(t_queue *q)
{
	int		i;
	int		best;
	t_coder	*coder;

	best = -1;
	i = 0;
	while (i < q->size)
	{
		if (is_valid_dongl_left_right(q->heap[i]->coder))
		{
			if (best == -1 || is_greater(q->heap[best], q->heap[i]))
				best = i;
		}
		i++;
	}
	if (best == -1)
		return (NULL);
	coder = q->heap[best]->coder;
	q->heap[best]->coder = q->heap[q->size - 1]->coder;
	q->heap[best]->deadline = q->heap[q->size - 1]->deadline;
	q->size--;
	heapify_down(q, best);
	heapify_up(q, best);
	return (coder);
}

t_coder	*pop_edf_or_fifo(t_queue *q, t_scheduler scheduler)
{
	t_coder	*coder;

	coder = NULL;
	if (scheduler == FIFO)
	{
		if (q->capacity == 1)
			return (NULL);
		coder = q->heap[0]->coder;
		if (!is_valid_dongl_left_right(q->heap[0]->coder))
			return (NULL);
		shift_queue_elements(q);
		q->size--;
	}
	else if (scheduler == EDF)
	{
		if (q->capacity == 1)
			return (NULL);
		coder = pop_highest_priority_ready_coder(q);
		return (coder);
	}
	return (coder);
}

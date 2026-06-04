/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 17:20:51 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/04 20:52:49 by moerrais         ###   ########.fr       */
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
		heapify_up(q, q->size);
	q->size++;
	pthread_mutex_unlock(&q->mutex_queue);
}

bool	try_take_dongle(t_dongle *dongle)
{
	bool	success;

	pthread_mutex_lock(&dongle->m_cn_dongle.mutex);
	if (!(get_time() - dongle->last_release_time >= dongle->cooldown_time))
	{
		pthread_mutex_unlock(&dongle->m_cn_dongle.mutex);
		return (false);
	}
	success = dongle->is_available;
	pthread_mutex_unlock(&dongle->m_cn_dongle.mutex);
	return (success);
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
	t_coder	*coder;
	int		i;

	i = 0;
	while (i < q->size)
	{
		printf("coders id %d  \n", q->heap[i]->coder->id);
		i++;
	}
	i = 0 ;
	while (i < q->size)
	{
		if (is_valid_dongl_left_right(q->heap[i]->coder))
		{
			coder = q->heap[i]->coder;
			q->heap[i]->coder = q->heap[q->size - 1]->coder;
			q->heap[i]->deadline = q->heap[q->size - 1]->deadline;
			q->size--;
			if (is_greater(q->heap[i], q->heap[parent_index(i)]))
				heapify_up(q, i);
			else
				heapify_down(q, i);
			return (coder);
		}
		i++;
	}
	return (NULL);
}

t_coder	*pop_queue(t_queue *q, t_scheduler scheduler)
{
	t_coder	*coder;
	int		i;

	coder = NULL;
	i = 1;
	pthread_mutex_lock(&q->mutex_queue);
	if (q->size == 0)
	{
		pthread_mutex_unlock(&q->mutex_queue);
		return (NULL);
	}
	if (scheduler == FIFO)
	{
		coder = q->heap[0]->coder;
		if (!is_valid_dongl_left_right(q->heap[0]->coder))
		{
			pthread_mutex_unlock(&q->mutex_queue);
			return (NULL);
		}
		shift_queue_elements(q);
		q->size--;
	}
	else if (scheduler == EDF)
	{
		// printf("is edf\n");
		coder = pop_highest_priority_ready_coder(q);
		pthread_mutex_unlock(&q->mutex_queue);
		// printf("id coder %d\n", coder->id);
		return (coder);
	}
	pthread_mutex_unlock(&q->mutex_queue);
	return (coder);
}

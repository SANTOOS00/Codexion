/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:08:45 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/29 01:02:40 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static t_coder	*pop_queue_edf(t_queue *q);
static t_coder	*pop_queue_fifo(t_queue *q);

t_coder	*pop_queue(t_simulation *sim, t_scheduler scheduler)
{
	t_coder	*coder;

	coder = NULL;
	pthread_mutex_lock(&sim->queue->mutex_queue);
	if (sim->queue->size <= 0)
	{
		pthread_mutex_unlock(&sim->queue->mutex_queue);
		return (NULL);
	}
	if (scheduler == FIFO)
		coder = pop_queue_fifo(sim->queue);
	else
		coder = pop_queue_edf(sim->queue);
	pthread_mutex_unlock(&sim->queue->mutex_queue);
	return (coder);
}

void	enqueue_initial_coders(t_coder *coder)
{
	t_queue	*queue;
	bool wait_watcher;

	wait_watcher = false;
	pthread_mutex_lock(&coder->queue->mutex_queue);
	queue = coder->queue;
	if (queue->size >= queue->capacity)
	{
		pthread_mutex_unlock(&coder->queue->mutex_queue);
		return ;
	}
	queue->coders[queue->size] = coder;
	queue->size++;
	pthread_mutex_unlock(&coder->queue->mutex_queue);
	
}

void	push_priority_queue(t_coder *coder)
{
	t_queue	*queue;

	queue = coder->queue;
	queue->coders[queue->size] = coder;
	if (coder->config->scheduler == EDF)
		heapify_up(queue, queue->size);
	queue->size++;
}

static t_coder	*pop_queue_edf(t_queue *q)
{
	t_coder	*coder;
	int		i;

	i = 0;
	coder = NULL;
	if (q->size == 0)
		return (NULL);
	while (i < q->size)
	{
		if (is_valid_dongl_left_right(q->coders[i]))
		{
			coder = q->coders[i];
			q->coders[i] = q->coders[q->size - 1];
			heapify_down(q, i);
			q->size--;
			return (coder);
		}
		i++;
	}
	return (coder);
}

static t_coder	*pop_queue_fifo(t_queue *q)
{
	t_coder	*coder;

	coder = NULL;
	coder = q->coders[0];
	if (!is_valid_dongl_left_right(q->coders[0]))
		return (NULL);
	shift_queue_elements(q);
	q->size--;
	return (coder);
}

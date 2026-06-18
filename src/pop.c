/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_fifo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:16:29 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/17 20:36:44 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	shift_queue_elements(t_queue *q)
{
	int	i;

	i = 1;
	while (i < q->size)
	{
		q->coders[i - 1] = q->coders[i];
		i++;
	}
}

t_coder	*pop_queue_fifo(t_queue *q)
{
	t_coder	*coder;

	coder = NULL;
	if (q->capacity == 1 || q->size == 0)
		return (NULL);
	pthread_mutex_lock(&q->mutex_queue);
	coder = q->coders[0];
	if (!is_valid_dongl_left_right(q->coders[0]))
	{
		pthread_mutex_unlock(&q->mutex_queue);
		return (NULL);
	}
	shift_queue_elements(q);
	q->size--;
	pthread_mutex_unlock(&q->mutex_queue);
	return (coder);
}

t_coder	*pop_queue_edf(t_queue *q)
{
	t_coder	*coder;

	pthread_mutex_lock(&q->mutex_queue);
	if (q->size == 0)
	{
		pthread_mutex_unlock(&q->mutex_queue);
		return (NULL);
	}
	if (is_valid_dongl_left_right(q->coders[0]))
	{
		coder = q->coders[0];
		q->coders[0] = q->coders[q->size - 1];
		q->size--;
		heapify_down(q, 0);
		pthread_mutex_unlock(&q->mutex_queue);
		return (coder);
	}
	pthread_mutex_unlock(&q->mutex_queue);
	return (NULL);
}

t_coder *pop_queue(t_simulation *sim, t_scheduler scheduler)
{
	if (scheduler == FIFO)
		return (pop_queue_fifo(sim->queue));
	return(pop_queue_edf(sim->queue));
}
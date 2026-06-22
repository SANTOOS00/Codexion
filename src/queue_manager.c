/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 02:40:02 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/22 16:28:41 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

t_coder	*pop_queue(t_simulation *sim, t_scheduler scheduler)
{
	t_coder		*coder;

	coder = NULL;
	pthread_mutex_lock(&sim->queue->mutex_queue);
	if (scheduler == FIFO)
		coder = pop_queue_fifo(sim->queue);
	else
	{
		if (!is_valid_dongl_left_right(sim->queue->coders[0]))
			move_first_valid_coder_to_front(sim->queue);
		coder = pop_queue_edf(sim->queue);
	}
	pthread_mutex_unlock(&sim->queue->mutex_queue);
	return (coder);
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

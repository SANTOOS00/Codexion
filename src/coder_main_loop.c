/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_main_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:50:54 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/23 06:52:27 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"



void	push_queue(t_coder *coder)
{
	t_queue	*queue;

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

void	enqueue_coder_and_wait(t_coder *coder)
{
	if (get_status_coder(coder) == START && coder->id % 2 != 0)
		usleep(1000);
	push_queue(coder);
	increment_coders_counter(coder);
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	coder->has_dongle = false;
	while (!coder->has_dongle)
		pthread_cond_wait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex);
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void	coder_main_loop(t_coder *coder)
{
	enqueue_coder_and_wait(coder);
	while (1)
	{
		if (!perform_coding(coder))
			break;
		
	}
}

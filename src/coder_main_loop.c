/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_main_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:50:54 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/13 18:18:15 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	update_burnout_timer(t_coder *coder, t_config config)
{
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	coder->deadline = get_time() + config.time_to_burnout;
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

t_coder_status	get_status_coder(t_coder *coder)
{
	t_coder_status	status;

	pthread_mutex_lock(&coder->mutex_cond.mutex);
	status = coder->status;
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
	return (status);
}

void	push_queue(t_coder *coder)
{
	t_queue	*queue;

	pthread_mutex_lock(&coder->queue->mutex_queue);
	queue = coder->queue;
	queue->coders[queue->size] = coder;
	queue->size++;
	pthread_mutex_unlock(&coder->queue->mutex_queue);
}

void enqueue_coder_and_wait(t_coder *coder)
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

void	enqueue_coder_request(t_coder *coder)
{
	pthread_mutex_lock(&coder->queue->mutex_queue);
	push_to_priority_queue(coder->queue, coder, coder->config->scheduler);
	pthread_mutex_unlock(&coder->queue->mutex_queue);

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
		perform_coding(coder);
		if (get_status_coder(coder) == FINISHED)
			break ;
		if (get_status_coder(coder) == IS_BURNOUT)
			break ;
		enqueue_coder_request(coder);
	}
}

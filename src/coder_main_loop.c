/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_main_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:50:54 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/24 04:31:18 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"


static bool	enqueue_coder_request(t_coder *coder);
void	increment_coders_counter(t_coder *coder);
static void	enqueue_coder_and_wait(t_coder *coder);
static void	push_queue(t_coder *coder);
static bool ft_is_finished(t_coder *coder);



void	coder_main_loop(t_coder *coder)
{
	enqueue_coder_and_wait(coder);
	while (1)
	{
		if (ft_is_finished(coder))	
			break;
		if (!perform_coding(coder))
			break;
		if (enqueue_coder_request(coder))
			break;
	}
}

static bool ft_is_finished(t_coder *coder)
{
	return (coder->compilation_count >= coder->config->number_of_compiles_required);
} 

bool	enqueue_coder_request(t_coder *coder)
{
  pthread_mutex_lock(&coder->queue->mutex_queue);
  push_priority_queue(coder);
  pthread_mutex_unlock(&coder->queue->mutex_queue);

  pthread_mutex_lock(&coder->mutex_cond.mutex);
  coder->has_dongle = false;
  while (!coder->has_dongle)
    pthread_cond_wait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex);
  pthread_mutex_unlock(&coder->mutex_cond.mutex);
  return (ft_is_simulation_finished(coder->is_finished_sim, coder->is_finished_sim_m));
}

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

static void	enqueue_coder_and_wait(t_coder *coder)
{
	if (coder->id % 2 != 0)
		usleep(1000);
	push_queue(coder);
	increment_coders_counter(coder);
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	coder->has_dongle = false;
	while (!coder->has_dongle)
		pthread_cond_wait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex);
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void	increment_coders_counter(t_coder *coder)
{
	pthread_mutex_lock(&coder->watcher_mu_cond->mutex);
	(*coder->run_coders_counter)++;
	pthread_cond_broadcast(&coder->watcher_mu_cond->cond);
	pthread_mutex_unlock(&coder->watcher_mu_cond->mutex);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:46:11 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/29 01:03:08 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static void	increment_coders_counter(t_coder *coder);
static bool	wait_all_coders_created(t_coder *coder);
static void	ft_coder_main_loop(t_coder *coder);
static void	enqueue_initial_coder_and_wait(t_coder *coder);

void	*ft_coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	increment_coders_counter(coder);
	if (!wait_all_coders_created(coder))
		return (NULL);
	ft_coder_main_loop(coder);
	return (NULL);
}

static void	increment_coders_counter(t_coder *coder)
{
	pthread_mutex_lock(&coder->watcher_mu_cond->mutex);
	(*coder->run_coders_counter)++;
	pthread_cond_broadcast(&coder->watcher_mu_cond->cond);
	pthread_mutex_unlock(&coder->watcher_mu_cond->mutex);
}

static bool	wait_all_coders_created(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	coder->is_waiting_coder = false;
	while (!coder->is_waiting_coder)
		pthread_cond_wait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex);
	if (coder->status == ERROR)
	{
		pthread_mutex_unlock(&coder->mutex_cond.mutex);
		return (false);
	}
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
	return (true);
}

static void	ft_coder_main_loop(t_coder *coder)
{
	enqueue_initial_coder_and_wait(coder);
	while (1)
	{
		if (!perform_coding(coder))
			break ;
		if (coder->status == FINISHED)
			break;
	}
}

static void	enqueue_initial_coder_and_wait(t_coder *coder)
{
	if (coder->id % 2 != 0)
		usleep(2000);
	
	enqueue_initial_coders(coder);
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	
	coder->has_dongle = false;
	while (!coder->has_dongle)
		pthread_cond_wait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex);
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

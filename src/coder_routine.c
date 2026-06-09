/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:46:11 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/05 15:56:37 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	increment_coders_counter(t_coder *coder)
{
	pthread_mutex_lock(&coder->coders_cnt_lock->mutex);
	(*coder->run_coders_counter)++;
	pthread_cond_broadcast(&coder->coders_cnt_lock->cond);
	pthread_mutex_unlock(&coder->coders_cnt_lock->mutex);
}

bool	wait_all_coders_created(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	
	coder->has_dongle = false;
	while (!coder->has_dongle)
		pthread_cond_wait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex);
	if (coder->status == ERROR)
	{
		pthread_mutex_unlock(&coder->mutex_cond.mutex);
		return (false);
	}
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
	return (true);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	increment_coders_counter(coder);
	if (wait_all_coders_created(coder) == false)
		return (NULL);
	coder_main_loop(coder);
	return (NULL);
}

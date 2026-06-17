/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:21:22 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/13 18:42:26 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void watcher_wake_coders(t_simulation *sim)
{
	int i;

	i = 0;
	while(i < sim->config.number_of_coders)
	{
		pthread_mutex_lock(&sim->coders[i]->mutex_cond.mutex);
		sim->coders[i]->is_waiting_coder = true;
		pthread_cond_broadcast(&sim->coders[i]->mutex_cond.cond);
		pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);
		i++;
	}
}
bool wait_watcher(t_simulation *sim)
{
	pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
	while (sim->run_coders_counter != sim->config.number_of_coders)
		pthread_cond_wait(&sim->coders_cnt_lock.cond,
			&sim->coders_cnt_lock.mutex);
	if (sim->monitor_status == ERROR_M)
	{
		pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
		return (false);	
	}
	pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
	return (true);
}

void	init_time_start(t_simulation *sim)
{
	pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
	sim->time_start = get_time();
	pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
}

void	*watcher_routine(void *arg)
{
	t_simulation *sim;

	sim = (t_simulation *)arg;
	if (wait_watcher(sim) == false)
		return (NULL);
	watcher_wake_monitor(sim);
	init_time_start(sim);
	watcher_wake_coders(sim);
	run_fifo_or_edf_routine(sim);
	return (NULL);
}


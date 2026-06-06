/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_coders_and_watcher.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 21:06:44 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/06 03:45:37 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	activate_watcher(t_simulation *sim)
{
	pthread_mutex_lock(&sim->watch_lock.mutex);
	sim->is_watch_waiting = true;
	pthread_cond_broadcast(&sim->watch_lock.cond);
	pthread_mutex_unlock(&sim->watch_lock.mutex);
}

void	activate_coders(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		pthread_mutex_lock(&sim->coders[i]->mutex_cond.mutex);
		sim->coders[i]->has_dongle = true;
		pthread_cond_broadcast(&sim->coders[i]->mutex_cond.cond);
		pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);
		i++;
	}
}

void	init_time_start(t_simulation *sim)
{
	pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
	sim->time_start = get_time();
	pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
}

bool	get_status_monitor(t_simulation *sim)
{
	bool	status;

	pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
	status = sim->is_burnout;
	pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
	return (status);
}

void	start_coder_and_watcher(t_simulation *sim)
{
	usleep(1500);
	activate_coders(sim);
	activate_watcher(sim);
	init_time_start(sim);
	run_fifo_or_edf_routine(sim);
}

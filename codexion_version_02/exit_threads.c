/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:46:14 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/14 21:12:25 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



void exit_monitor_tid(t_simulation *sim)
{
	pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
	sim->monitor_status = ERROR_M;
	sim->run_coders_counter = sim->config.number_of_coders;
	pthread_cond_broadcast(&sim->coders_cnt_lock.cond);
	pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
	join_monitor(sim);
}


void exit_watcher_tid(t_simulation *sim)
{
	pthread_mutex_lock(&sim->watch_lock.mutex);
	sim->watch_status = ERROR_W;
	sim->is_watch_waiting = true;
	pthread_cond_broadcast(&sim->watch_lock.cond);
	pthread_mutex_unlock(&sim->watch_lock.mutex);
	join_watcher_tid(sim);
}

void exit_thread(t_simulation *sim, int size_threads_create)
{
	int i;
	
	i = 0;
	usleep(1000);
	while(i < size_threads_create)
	{
		pthread_mutex_lock(&sim->coders[i]->mutex_cond.mutex);
		sim->coders[i]->has_dongle = true;
		sim->coders[i]->status = ERROR;
		pthread_cond_broadcast(&sim->coders[i]->mutex_cond.cond);
		pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);
		i++;
	}
	join_coders(sim, size_threads_create);
}
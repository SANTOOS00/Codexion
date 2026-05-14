/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:37:59 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/14 21:21:26 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


void *monitor_routine(void *arg)
{
	t_simulation *sim;

	sim = (t_simulation *)arg;
	pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
	while (sim->run_coders_counter != sim->config.number_of_coders && sim->monitor_status != ERROR_M)
		pthread_cond_wait(&sim->coders_cnt_lock.cond, &sim->coders_cnt_lock.mutex);
	if (sim->monitor_status == ERROR_M)
	{
		pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
		return (NULL);
	}
	pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
	initiate_crossing_logic(sim);
	return (NULL);
}

void join_monitor(t_simulation *sim)
{
	pthread_join(sim->monitor_tid, NULL);
	printf("error\n");
}

void join_watcher_tid(t_simulation *sim)
{
	pthread_join(sim->watcher_tid, NULL);
	printf("error\n");
}

bool run_monitor_simulation(t_simulation *sim)
{
	if(pthread_create(&sim->monitor_tid, NULL, monitor_routine, sim) != 0)
		return (false);
	if (pthread_create(&sim->watcher_tid, NULL, watcher_tid_routine, sim) != 0)
	{
		exit_monitor_tid(sim);
		return (false);
	}
	return (true);
}

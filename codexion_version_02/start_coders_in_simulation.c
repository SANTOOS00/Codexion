/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_coders_in_simulation.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:42:54 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/15 21:10:10 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



void finich_monitor_and_watcher(t_simulation *sim)
{
	pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
	sim->monitor_status = FINISHED_M;
	pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
	pthread_mutex_lock(&sim->watch_lock.mutex);
	sim->watch_status = FINISHED_W;
	pthread_mutex_unlock(&sim->watch_lock.mutex);
}

void *coders_routine(void *arg)
{
	t_coder *coder;

	coder = (t_coder *)arg;	
	pthread_mutex_lock(&coder->coders_cnt_lock->mutex);
	(*coder->run_coders_counter)++;
	pthread_cond_broadcast(&coder->coders_cnt_lock->cond);
	pthread_mutex_unlock(&coder->coders_cnt_lock->mutex);

	pthread_mutex_lock(&coder->mutex_cond.mutex);
	coder->has_dongle = false;
    while (!coder->has_dongle)
		pthread_cond_wait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex);
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
	execute_coder_workflow(coder);

	return (NULL);
}

void join_coders(t_simulation *sim, int number_coder_create)
{
	int i;

	i = 0;

	while(i < number_coder_create)
		pthread_join(sim->coders[i++]->thread, NULL);
}

void join_threads(t_simulation *sim)
{
	join_coders(sim, sim->config.number_of_coders);
	finich_monitor_and_watcher(sim);
	join_watcher_tid(sim);
	join_monitor(sim);
}

bool start_coders_in_simulation(t_simulation *sim)
{
	int i;
	int ret;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		if ((ret = pthread_create(&sim->coders[i]->thread, NULL, coders_routine, sim->coders[i])))
		{
			fprintf(stderr, "Error: pthread_create failed: %s \nid coder failed %d\n", strerror(ret), i);
			exit_watcher_tid(sim);
			exit_monitor_tid(sim);
			exit_thread(sim, i);
			return (false);
		}
		i++;
	}
	join_threads(sim);
	return (true);
}
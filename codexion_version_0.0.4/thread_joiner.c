/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_joiner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:23:15 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/16 14:44:39 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void join_monitor(t_simulation *sim)
{
	pthread_join(sim->monitor_tid, NULL);
}

void join_watcher(t_simulation *sim)
{
	pthread_join(sim->watcher_tid, NULL);
}

void join_coders(t_simulation *sim, int number_coders)
{
    int i;

    i = 0;
    while(i < sim->config.number_of_coders)
        pthread_join(sim->coders[i++]->thread, NULL);
}

void finich_monitor_and_watcher(t_simulation *sim)
{
	pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
	sim->monitor_status = FINISHED_M;
	pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
	pthread_mutex_lock(&sim->watch_lock.mutex);
	sim->watch_status = FINISHED_W;
	pthread_mutex_unlock(&sim->watch_lock.mutex);
}

void join_threads(t_simulation *sim)
{
    join_coders(sim, sim->config.number_of_coders);
    finich_monitor_and_watcher(sim);
    join_monitor(sim);
    join_watcher(sim);
}
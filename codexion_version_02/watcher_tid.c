/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_tid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 16:17:56 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/13 17:07:06 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


void print(t_simulation *sim)
{
    int i;
    int size;

    pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
    size = sim->config.number_of_coders;
    pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
    i = 0;
    while (true)
    {
        pthread_mutex_lock(&sim->coders[i]->mutex_cond.mutex);
        if (sim->coders[i]->deadline != 0 && sim->coders[i]->deadline <= get_time())
        {
            pthread_mutex_lock(&sim->burnout_mutex);
            sim->is_burnout = true;
            printf("is bournout ssssss\n");
            pthread_mutex_unlock(&sim->burnout_mutex);
            pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);
            break;
        }
        pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);
        i++;
        if (i == size)
            usleep(1000);
    }
}

void *watcher_tid_routine(void *arg)
{
	t_simulation *sim;
	
	sim = (t_simulation *)arg; 
	pthread_mutex_lock(&sim->watch_lock.mutex);
	while (!sim->is_watch_waiting)
		pthread_cond_wait(&sim->watch_lock.cond, &sim->watch_lock.mutex);
	if (sim->watch_status == ERROR_W)
		return (NULL);
	pthread_mutex_unlock(&sim->watch_lock.mutex);
    // print(sim);
	return (NULL);
}
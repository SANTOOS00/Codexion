/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_tid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 16:17:56 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/14 12:07:23 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



void exit_coders(t_coder **coders, int size)
{
    int i;

    i = 0;
    while(i < size)
    {
        pthread_mutex_lock(&coders[i]->mutex_cond.mutex);
        coders[i]->status = ERROR;
        coders[i]->has_dongle = true;
        pthread_cond_broadcast(&coders[i]->mutex_cond.cond);
        pthread_mutex_unlock(&coders[i]->mutex_cond.mutex);  
        i++;
    }
}

void test(t_simulation *sim)
{
    int i;
    int size = 10;
    long long time_coder;
    int id;

    pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
    size = sim->config.number_of_coders;
    pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
    i = 0;
    while (true)
    {
        pthread_mutex_lock(&sim->watch_lock.mutex);
        if (sim->monitor_status == FINISHED_W)
        {
            pthread_mutex_unlock(&sim->watch_lock.mutex);
            break;   
        }
        pthread_mutex_unlock(&sim->watch_lock.mutex);
        pthread_mutex_lock(&sim->coders[i]->mutex_cond.mutex);
        time_coder = sim->coders[i]->deadline;
        id = sim->coders[i]->id;
        pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);

        if (time_coder != 0 && get_time() > time_coder)
        {
            printf("\nburnout ok coder id %d time get %lld, time _coder %lld\n\n", id, get_time(), time_coder);
            pthread_mutex_lock(&sim->burnout_mutex);
            sim->is_burnout = true;
            pthread_mutex_unlock(&sim->burnout_mutex);
            exit_coders(sim->coders, size);
            break;
        }
        i++;
        if (i == size)
        {
            i = 0;
            usleep(1000);
        }
        
        // pthread_mutex_lock(&sim->queue->mutex_queue);
        // if (sim->queue->size == 0)
        // {
        //     pthread_mutex_unlock(&sim->queue->mutex_queue);
        //     break;
        // }
        // pthread_mutex_unlock(&sim->queue->mutex_queue);
    }
   
    // stop_coder(sim->queue, sim->crossing);
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
    test(sim);
    printf("finich test\n");
	return (NULL);
}
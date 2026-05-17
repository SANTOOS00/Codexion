/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:21:22 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/16 14:47:13 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_watch_status get_status_watcher(t_simulation *sim)
{
	t_watch_status status;
	pthread_mutex_lock(&sim->watch_lock.mutex);
	status = sim->watch_status;
	pthread_mutex_unlock(&sim->watch_lock.mutex);
	return (status);
}


void detect_burnout_in_coders(t_simulation *sim)
{
	int i;


	i = 0;
	while (1)
	{
		if (get_status_watcher(sim) == FINISHED_W)
			break;
		while (i < sim->config.number_of_coders)
		{
			if (get_status_watcher(sim) == FINISHED_W)
				break;
			if (get_status_coder(sim->coders[i]) != FINISHED)
			{
				pthread_mutex_lock(&sim->coders[i]->mutex_cond.mutex);
				if(get_time() > sim->coders[i]->deadline)
				{
					printf("is bournout\n");
					
				}
				pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);
			}
			i++;
		}
		i = 0;
	}
}

void *watcher_routine(void *arg)
{
	t_simulation *sim;

	sim = (t_simulation *)arg;
	pthread_mutex_lock(&sim->watch_lock.mutex);
	while (!sim->is_watch_waiting)
		pthread_cond_wait(&sim->watch_lock.cond, &sim->watch_lock.mutex);
	if (sim->watch_status == ERROR_W)
    {
        pthread_mutex_unlock(&sim->watch_lock.mutex);
		return (NULL);
    }
	pthread_mutex_unlock(&sim->watch_lock.mutex);
	detect_burnout_in_coders(sim);
	return (NULL);
}
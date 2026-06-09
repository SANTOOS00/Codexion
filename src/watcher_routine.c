/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:21:22 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/05 19:51:23 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

t_watch_status	get_status_watcher(t_simulation *sim)
{
	t_watch_status	status;

	pthread_mutex_lock(&sim->watch_lock.mutex);
	status = sim->watch_status;
	pthread_mutex_unlock(&sim->watch_lock.mutex);
	return (status);
}

void	detect_burnout_in_coders(t_simulation *sim)
{
	bool	ischeckboun;
	int		i;
	ischeckboun = false;
	while (!ischeckboun)
	{
		i = 0;
		if (get_status_watcher(sim) == FINISHED_W)
			break ;
		while (!ischeckboun && i < sim->config.number_of_coders)
		{
			// if (get_status_coder(sim->coders[i]) == START)
			// 	i++;
			if (get_status_watcher(sim) == FINISHED_W)
				break ;
			else if (get_status_coder(sim->coders[i]) != FINISHED)
			{
				if (check_coder_burnout(sim, i))
					ischeckboun = true;
				i++;
			}
		}
		if (ischeckboun)
			break ;
	}
}

void	*watcher_routine(void *arg)
{
	t_simulation	*sim;

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

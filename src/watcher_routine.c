/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:21:22 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/02 22:16:42 by moerrais         ###   ########.fr       */
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

void	stop_coders(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		pthread_mutex_lock(&sim->coders[i]->mutex_cond.mutex);
		sim->coders[i]->status = IS_BURNOUT;
		sim->coders[i]->has_dongle = true;
		pthread_cond_broadcast(&sim->coders[i]->mutex_cond.cond);
		pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);
		i++;
	}
}

void	stop_monitor(t_simulation *sim)
{
	pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
	sim->monitor_status = FINISHED_M;
	pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
}

void	detect_burnout_in_coders(t_simulation *sim)
{
	int		i;
	bool	is_Check_boun;

	is_Check_boun = false;
	while (1)
	{
		i = 0;
		if (get_status_watcher(sim) == FINISHED_W)
			break ;
		while (i < sim->config.number_of_coders)
		{
			if (get_status_watcher(sim) == FINISHED_W)
				break ;
			if (get_status_coder(sim->coders[i]) != FINISHED)
			{
				pthread_mutex_lock(&sim->coders[i]->mutex_cond.mutex);
				if (sim->coders[i]->deadline != 0
					&& get_time() > sim->coders[i]->deadline)
				{
					pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);
					stop_monitor(sim);
					stop_coders(sim);
					print_coder_action(sim->coders[i], "is bournout");
					is_Check_boun = true;
					break ;
				}
				else
				{
					pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);
					usleep(1000);
				}
			}
			if (is_Check_boun)
				break ;
			i++;
		}
		if (is_Check_boun)
			break ;
	}
}

void	*watcher_routine(void *arg)
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
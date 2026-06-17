/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:21:10 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/17 23:04:37 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"


t_monitor_status	get_status_monitor(t_simulation *sim)
{
	t_monitor_status	status;

	pthread_mutex_lock(&sim->watch_lock.mutex);
	status = sim->monitor_status;
	pthread_mutex_unlock(&sim->watch_lock.mutex);
	return (status);
}

// bool wait_monitor(t_simulation *sim)
// {
// 	pthread_mutex_lock(sim->)
// 	pthread_cond_timedwait()
// }

void	detect_burnout_in_coders(t_simulation *sim)
{
	bool	ischeckboun;
	int		i;
	ischeckboun = false;
	while (!ischeckboun)
	{
		i = 0;
		if (get_status_monitor(sim) == FINISHED_M)
			break ;
		while (!ischeckboun && i < sim->config.number_of_coders)
		{
			if (get_status_coder(sim->coders[i]) != FINISHED)
			{
				if (check_coder_burnout(sim, i))
				{
					ischeckboun = true;
					break;
				}
			}
			i++;
		}
		if (wait_monitor(sim) == false)
			break;
		if (ischeckboun)
			break ;
	}
}

bool wait_monitor(t_simulation *sim)
{
	pthread_mutex_lock(&sim->watch_lock.mutex);
	while (!sim->is_watch_waiting)
		pthread_cond_wait(&sim->watch_lock.cond, &sim->watch_lock.mutex);
	if (sim->monitor_status == ERROR_W)
	{
		pthread_mutex_unlock(&sim->watch_lock.mutex);
		return (false);
	}
	pthread_mutex_unlock(&sim->watch_lock.mutex);
	return (true);
}

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	if (wait_monitor(sim) == false)
		return (NULL);
	detect_burnout_in_coders(sim);
	return (NULL);
}

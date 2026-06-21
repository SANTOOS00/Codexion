/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:21:10 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/21 22:33:02 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

bool	wait_monitor(t_simulation *sim)
{
	pthread_mutex_lock(&sim->monitor_mu_cond.mutex);
	sim->is_watch_waiting = false;
	while (!sim->is_watch_waiting)
		pthread_cond_wait(&sim->monitor_mu_cond.cond,
			&sim->monitor_mu_cond.mutex);
	if (sim->monitor_status == ERROR_W || sim->monitor_status == FINISHED_M)
	{
		pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
		return (false);
	}
	pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
	return (true);
}



void wait_monitor_nons()
{
    struct timespec ts;

    ts.tv_sec  = 0;
    ts.tv_nsec = 100;
    nanosleep(&ts, NULL);
}

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
					break ;
				}
			}
			i++;
		}
		wait_monitor_nons();
	}
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

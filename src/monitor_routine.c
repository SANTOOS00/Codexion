/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:21:10 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/20 04:54:21 by santoos          ###   ########.fr       */
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
	if (sim->monitor_status == ERROR_M || sim->monitor_status == FINISHED_M)
	{
		pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
		return (false);
	}
	pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
	return (true);
}

bool test_name_1(t_simulation *sim)
{
	int i;

	i = 0;
	while (i < sim->queue->size)
	{
		
		if (get_status_coder(sim->queue->coders[i]) != FINISHED)
		{
			if (check_coder_burnout(sim, i))
				return (true);
		}
		i++;
	}
	return (false);
}

void	detect_burnout_in_coders(t_simulation *sim)
{
	bool	ischeckboun;

	ischeckboun = false;
	while (!ischeckboun)
	{
		if (get_status_monitor(sim) == FINISHED_M)
			break ;
		pthread_mutex_lock(&sim->queue->mutex_queue);
		if (test_name_1(sim) == true)
			return ;
		pthread_mutex_unlock(&sim->queue->mutex_queue);
		usleep(20);
	}
}

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	if (wait_monitor(sim) == false)
		return (NULL);
	detect_burnout_in_coders(sim);
	printf("finich monitor \n");
	return (NULL);
}

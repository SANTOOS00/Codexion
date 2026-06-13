/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_coder_burnout.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:36:24 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/12 17:02:28 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

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

bool check_coder_burnout(t_simulation *sim, int i)
{
	bool burned = false;

	pthread_mutex_lock(&sim->coders[i]->mutex_cond.mutex);
	if (sim->coders[i]->deadline != 0 &&
		get_time() >= sim->coders[i]->deadline)
	{
		burned = true;
	}
	pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);
	if (burned)
	{
		stop_monitor(sim);
		stop_coders(sim);
		print_coder_action(sim->coders[i], "is burnout");
		return true;
	}
	usleep(1000);
	return false;
}

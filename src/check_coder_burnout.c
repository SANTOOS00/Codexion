/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_coder_burnout.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:36:24 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/20 03:59:43 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	monitor_stop_coders(t_simulation *sim)
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

void	monitor_stop_watcher(t_simulation *sim)
{
	pthread_mutex_lock(&sim->watch_mu_cond.mutex);
	sim->watch_status = FINISHED_W;
	pthread_mutex_unlock(&sim->watch_mu_cond.mutex);
}

bool	check_coder_burnout(t_simulation *sim, int i)
{
	bool	burned;

	burned = false;
	pthread_mutex_lock(&sim->queue->coders[i]->mutex_cond.mutex);
	if (sim->queue->coders[i]->deadline != 0 && get_time() > sim->queue->coders[i]->deadline)
	{
		burned = true;
	}
	pthread_mutex_unlock(&sim->queue->coders[i]->mutex_cond.mutex);
	if (burned)
	{
		monitor_stop_watcher(sim);
		monitor_stop_coders(sim);
		print_coder_action(sim->coders[i], "is burnout");
		return (true);
	}
	usleep(50);
	return (false);
}

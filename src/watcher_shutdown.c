/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_shutdown.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 22:03:27 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/17 22:17:42 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	watcher_stop_coders(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		pthread_mutex_lock(&sim->coders[i]->mutex_cond.mutex);
		sim->coders[i]->status = FINISHED;
		sim->coders[i]->has_dongle = true;
		pthread_cond_broadcast(&sim->coders[i]->mutex_cond.cond);
		pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);
		i++;
	}
}

void	watcher_stop_monitor(t_simulation *sim)
{
	pthread_mutex_lock(&sim->watch_mu_cond.mutex);
	sim->monitor_status = FINISHED_M;
	sim->is_watch_waiting = true;
	pthread_cond_broadcast(&sim->monitor_mu_cond.cond);
	pthread_mutex_unlock(&sim->watch_mu_cond.mutex);
}
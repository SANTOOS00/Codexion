/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:46:14 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/27 03:53:44 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	exit_monitor(t_simulation *sim)
{
	pthread_mutex_lock(&sim->monitor_mu_cond.mutex);
	sim->monitor_status = ERROR_M;
	sim->run_coders_counter = sim->config.number_of_coders;
	pthread_cond_broadcast(&sim->monitor_mu_cond.cond);
	pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
	join_monitor(sim);
}

void	exit_watcher(t_simulation *sim)
{
	pthread_mutex_lock(&sim->watch_mu_cond.mutex);
	sim->watch_status = ERROR_W;
	sim->is_watch_waiting = true;
	pthread_cond_broadcast(&sim->watch_mu_cond.cond);
	pthread_mutex_unlock(&sim->watch_mu_cond.mutex);
	join_watcher(sim);
}

void	exit_coders(t_simulation *sim, int number_coders)
{
	int	i;

	i = 0;
	usleep(1000);
	while (i < number_coders)
	{
		pthread_mutex_lock(&sim->coders[i]->mutex_cond.mutex);
		sim->coders[i]->has_dongle = true;
		sim->coders[i]->status = ERROR;
		pthread_cond_broadcast(&sim->coders[i]->mutex_cond.cond);
		pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);
		i++;
	}
	join_coders(sim, number_coders);
}

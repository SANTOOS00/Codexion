/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_joiner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:23:15 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/20 02:30:04 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	join_monitor(t_simulation *sim)
{
	pthread_join(sim->monitor_tid, NULL);
}

void	join_watcher(t_simulation *sim)
{
	pthread_join(sim->watcher_tid, NULL);
}

void	join_coders(t_simulation *sim, int number_coders)
{
	int	i;

	i = 0;
	while (i < number_coders)
		pthread_join(sim->coders[i++]->thread, NULL);
}

void	finich_monitor_and_watcher(t_simulation *sim)
{
	pthread_mutex_lock(&sim->monitor_mu_cond.mutex);
	sim->monitor_status = FINISHED_M;
	pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
	pthread_mutex_lock(&sim->watch_mu_cond.mutex);
	sim->watch_status = FINISHED_W;
	pthread_mutex_unlock(&sim->watch_mu_cond.mutex);
}

void	join_threads(t_simulation *sim)
{
	join_coders(sim, sim->config.number_of_coders);
	finich_monitor_and_watcher(sim);
	join_monitor(sim);
	join_watcher(sim);
}

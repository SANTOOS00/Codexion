/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:21:22 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/27 03:53:34 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static void	watcher_wake_monitor(t_simulation *sim);
static bool	wait_watcher(t_simulation *sim);
static void	watcher_wait_coders(t_coder **coders, int nu_of_coders);
static void	set_simulation_start_time(t_simulation *sim);

void	*ft_watcher_routine(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	if (!wait_watcher(sim))
		return (NULL);
	watcher_wake_monitor(sim);
	set_simulation_start_time(sim);
	watcher_wait_coders(sim->coders, sim->config.number_of_coders);
	run_scheduler_loop(sim);
	return (NULL);
}

static bool	wait_watcher(t_simulation *sim)
{
	pthread_mutex_lock(&sim->watch_mu_cond.mutex);
	while (sim->run_coders_counter != sim->config.number_of_coders)
		pthread_cond_wait(&sim->watch_mu_cond.cond, &sim->watch_mu_cond.mutex);
	if (sim->monitor_status == ERROR_M)
	{
		pthread_mutex_unlock(&sim->watch_mu_cond.mutex);
		return (false);
	}
	pthread_mutex_unlock(&sim->watch_mu_cond.mutex);
	return (true);
}

static void	watcher_wake_monitor(t_simulation *sim)
{
	pthread_mutex_lock(&sim->monitor_mu_cond.mutex);
	sim->is_watch_waiting = true;
	pthread_cond_broadcast(&sim->monitor_mu_cond.cond);
	pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
}

static void	set_simulation_start_time(t_simulation *sim)
{
	pthread_mutex_lock(&sim->monitor_mu_cond.mutex);
	sim->time_start = get_time();
	pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
}

static void	watcher_wait_coders(t_coder **coders, int nu_of_coders)
{
	int	i;

	i = 0;
	while (i < nu_of_coders)
	{
		pthread_mutex_lock(&coders[i]->mutex_cond.mutex);
		coders[i]->is_waiting_coder = true;
		pthread_cond_broadcast(&coders[i]->mutex_cond.cond);
		pthread_mutex_unlock(&coders[i]->mutex_cond.mutex);
		i++;
	}
}

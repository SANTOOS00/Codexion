/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:21:22 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/23 05:37:39 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"
static void	watcher_wake_monitor(t_simulation *sim);
static void	run_fifo_or_edf(t_simulation *sim);
static bool ft_is_finished_simulation(t_simulation *sim);
static bool	wait_watcher(t_simulation *sim);
static void watcher_wait_coders(t_coder **coders, int nu_of_coders);
static void	set_simulation_start_time(t_simulation *sim);

void	*watcher_routine(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	if (!wait_watcher(sim))
		return (NULL);
	watcher_wake_monitor(sim);
	set_simulation_start_time(sim);
	watcher_wait_coders(sim->coders, sim->config.number_of_coders);
	run_fifo_or_edf(sim);
	return (NULL);
}

static void	set_simulation_start_time(t_simulation *sim)
{
	pthread_mutex_lock(&sim->monitor_mu_cond.mutex);
	sim->time_start = get_time();
	pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
}

static void	watcher_wake_monitor(t_simulation *sim)
{
	pthread_mutex_lock(&sim->monitor_mu_cond.mutex);
	sim->is_watch_waiting = true;
	pthread_cond_broadcast(&sim->monitor_mu_cond.cond);
	pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
}
void	run_fifo_or_edf(t_simulation *sim)
{
	t_coder		*coder;

	while (!ft_is_simulation_finished(&sim->is_finished_sim, &sim->is_finished_sim_m))
	{
		if (ft_is_finished_simulation(sim))
			break;
		coder = pop_queue(sim, sim->config.scheduler);
		if (!coder)
			usleep(300);
		else
		{
			pick_up_dongle(coder);
			update_burnout_timer(coder);
			pthread_mutex_lock(&coder->mutex_cond.mutex);
			coder->has_dongle = true;
			pthread_cond_broadcast(&coder->mutex_cond.cond);
			pthread_mutex_unlock(&coder->mutex_cond.mutex);
		}
	}
}


bool ft_is_finished_simulation(t_simulation *sim)
{
	bool is_finished_sim;

	is_finished_sim = false;
	pthread_mutex_lock(&sim->finished_coders_m);
	if (sim->finished_coders == sim->config.number_of_coders)
		is_finished_sim = true;
	pthread_mutex_unlock(&sim->finished_coders_m);
	
	pthread_mutex_lock(&sim->is_finished_sim_m);
	sim->is_finished_sim = is_finished_sim;
	pthread_mutex_unlock(&sim->is_finished_sim_m);
	return (is_finished_sim);
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


static void watcher_wait_coders(t_coder **coders, int nu_of_coders)
{
	int i;

	i = 0;
	while(i < nu_of_coders)
	{
		pthread_mutex_lock(&coders[i]->mutex_cond.mutex);
		coders[i]->is_waiting_coder = true;
		pthread_cond_broadcast(&coders[i]->mutex_cond.cond);
		pthread_mutex_unlock(&coders[i]->mutex_cond.mutex);
		i++;
	}
}
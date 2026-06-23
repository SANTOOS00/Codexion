/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:21:10 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/23 05:43:10 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"
#include <pthread.h>

static void signal_coders_to_stop(t_coder **coders, int number_of_coders);
static bool is_finished_watcher(t_simulation *sim);

bool	wait_monitor(t_simulation *sim)
{
	pthread_mutex_lock(&sim->monitor_mu_cond.mutex);
	sim->is_watch_waiting = false;
	while (!sim->is_watch_waiting)
		pthread_cond_wait(&sim->monitor_mu_cond.cond,
			&sim->monitor_mu_cond.mutex);
	if (sim->monitor_status == ERROR_M)
	{
		pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
		return (false);
	}
	pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
	return (true);
}

void ft_is_burnout(bool *is_burnout_detected, pthread_mutex_t *is_burnout_detected_m)
{
	pthread_mutex_lock(is_burnout_detected_m);
	(*is_burnout_detected) = true;
	pthread_mutex_unlock(is_burnout_detected_m);
}

bool ft_is_burnout_detected(t_coder **coders, int number_of_coders)
{
  	int i;

  	i = 0;
  	while (i < number_of_coders)
  	{
		if (check_coder_burnout(coders[i]))
		{
			ft_is_burnout(coders[i]->is_finished_sim, coders[i]->is_finished_sim_m);
			signal_coders_to_stop(coders, number_of_coders);
			print_coder_action(coders[i], "is burnout");
			return true;
		}
    	i++;
  	}
  	return false;
}

static void	detect_burnout_in_coders(t_simulation *sim)
{
 	while (!ft_is_burnout_detected(sim->coders, sim->config.number_of_coders) &&
    	!is_finished_watcher(sim))
    	usleep(300);
}

static void signal_coders_to_stop(t_coder **coders, int number_of_coders) {
	int	i;

	i = 0;
	while (i < number_of_coders)
	{
		pthread_mutex_lock(&coders[i]->mutex_cond.mutex);
		coders[i]->has_dongle = true;
		pthread_cond_broadcast(&coders[i]->mutex_cond.cond);
		pthread_mutex_unlock(&coders[i]->mutex_cond.mutex);
		i++;
	}
}

static bool is_finished_watcher(t_simulation *sim)
{
	bool is_finised;

	is_finised = false;
	pthread_mutex_lock(&sim->is_finished_sim_m);
	is_finised = sim->is_finished_sim;
	pthread_mutex_unlock(&sim->is_finished_sim_m);
	return (is_finised);
}

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	if (!wait_monitor(sim))
		return (NULL);
	detect_burnout_in_coders(sim);
	return (NULL);
}

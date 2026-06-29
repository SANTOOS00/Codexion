/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:21:10 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/29 00:58:15 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static bool	ft_is_finished_watcher(t_simulation *sim);
static bool	ft_wait_monitor(t_simulation *sim);
static void	ft_detect_burnout_in_coders(t_simulation *sim);
static bool	ft_is_finished_watcher(t_simulation *sim);
static bool	ft_is_burnout_detected(t_coder **coders, int number_of_coder);

void	*ft_monitor_routine(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	if (!ft_wait_monitor(sim))
		return (NULL);
	ft_detect_burnout_in_coders(sim);
	return (NULL);
}

static bool	ft_wait_monitor(t_simulation *sim)
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
void	ft_stop_simulation(t_simulation *sim)
{
	int i;

	i  = 0;
	while (i < sim->config.number_of_coders)
	{
		pthread_mutex_lock(&sim->coders[i]->mutex_cond.mutex);
		sim->coders[i]->has_dongle = true;
		sim->coders[i]->status = FINISHED;
		pthread_cond_broadcast(&sim->coders[i]->mutex_cond.cond);
		pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);
		i++;
	}
}

void monitor_finished_watcher(t_simulation *sim)
{
	pthread_mutex_lock(&sim->watch_mu_cond.mutex);	
	sim->watch_status = FINISHED_W;
	pthread_mutex_unlock(&sim->watch_mu_cond.mutex);	
}

static void	ft_detect_burnout_in_coders(t_simulation *sim)
{
	while (!ft_is_burnout_detected(sim->coders, sim->config.number_of_coders)
		&& !ft_is_finished_watcher(sim))
		usleep(300);
	monitor_finished_watcher(sim);
	ft_stop_simulation(sim);

}


static bool	ft_is_burnout_detected(t_coder **coders, int number_of_coders)
{
	int	i;

	i = 0;
	while (i < number_of_coders)
	{
		if (ft_check_coder_burnout(coders[i])
			&& !ft_is_finished_coder(coders[i]))
		{
			ft_is_burnout(coders[i]->is_finished_sim,
				coders[i]->is_finished_sim_m);
			ft_print_action(coders[i], "is burnout");
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	ft_is_finished_watcher(t_simulation *sim)
{
	bool		is_finised;

	is_finised = false;
	pthread_mutex_lock(&sim->is_finished_sim_m);
	is_finised = sim->is_finished_sim;
	pthread_mutex_unlock(&sim->is_finished_sim_m);
	return (is_finised);
}

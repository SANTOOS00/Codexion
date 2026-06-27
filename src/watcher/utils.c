/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 04:52:11 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/27 12:43:21 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

t_watch_status	ft_get_status_watcher(t_simulation *sim)
{
	t_watch_status	status;

	pthread_mutex_lock(&sim->watch_mu_cond.mutex);
	status = sim->watch_status;
	pthread_mutex_unlock(&sim->watch_mu_cond.mutex);
	return (status);
}

void	ft_stop_simulation(t_simulation *sim)
{
	pthread_mutex_lock(&sim->is_finished_sim_m);
	sim->is_finished_sim = true;
	pthread_mutex_unlock(&sim->is_finished_sim_m);
}

// static bool ft_is_burnout(bool *is_burnout, pthread_mutex_t *mutex)
// {
// 	bool is_check_burnout;

// 	is_check_burnout = false;
// 	pthread_mutex_lock(mutex);
// 	is_check_burnout = is_burnout;
// 	pthread_mutex_unlock(mutex);
// 	return (is_check_burnout);
// }

// bool ft_is_finished_simulation(t_simulation *sim)
// {
// 	bool is_finished_sim;

// 	is_finished_sim = false;
// 	pthread_mutex_lock(&sim->finished_coders_m);
// 	if (sim->finished_coders == sim->config.number_of_coders)
// 		is_finished_sim = true;
// 	pthread_mutex_unlock(&sim->finished_coders_m);

// 	pthread_mutex_lock(&sim->is_finished_sim_m);
// 	sim->is_finished_sim = is_finished_sim;
// 	pthread_mutex_unlock(&sim->is_finished_sim_m);
// 	return (is_finished_sim);
// }

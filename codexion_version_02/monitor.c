/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:37:59 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/07 03:07:52 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void *monitor_routine(void *arg)
{
	t_simulation *sim;

	sim = (t_simulation *)arg;
	pthread_mutex_lock(&sim->coders_counter_m_c.mutex);
	while (sim->run_coders_counter != sim->config.number_of_coders)
		pthread_cond_wait(&sim->coders_counter_m_c.cond, &sim->coders_counter_m_c.mutex);
	pthread_mutex_unlock(&sim->coders_counter_m_c.mutex);
	if (ft_fifo_or_edf(sim) == false)
		return (NULL);
	return (NULL);
}

void *join_monitor(t_simulation *sim)
{
	void *arg_ret;
	pthread_join(sim->thread, arg_ret);
	return (arg_ret);
}

bool run_monitor_simulation(t_simulation *sim)
{
	if(pthread_create(&sim->thread, NULL, monitor_routine, sim) != 0)
		return (false);
	return (true);
}

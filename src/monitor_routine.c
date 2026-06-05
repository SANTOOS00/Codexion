/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:21:10 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/04 21:21:09 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
	while (sim->run_coders_counter != sim->config.number_of_coders)
		pthread_cond_wait(&sim->coders_cnt_lock.cond,
			&sim->coders_cnt_lock.mutex);
	if (sim->monitor_status == ERROR_M)
	{
		pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
		return (NULL);
	}
	pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
	start_coder_and_watcher(sim);
	return (NULL);
}

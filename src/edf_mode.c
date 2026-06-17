/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 21:58:28 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/17 22:53:14 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

t_watch_status	get_watcher_status(t_simulation *sim)
{
	t_watch_status	check_status;

	pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
	check_status = sim->watch_status;
	pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
	return (check_status);
}

void	run_edf_routine(t_simulation *sim)
{
	t_coder	*coder;
	int		*i;
	int		conct;

	conct = 0;
	while (get_watcher_status(sim) != FINISHED_W)
	{
		if (is_burnout(sim) || conct == sim->config.number_of_coders)
			break ;
		coder = pop_queue_edf(sim->queue);
		if (!coder)
			usleep(500);
		else if (coder->compilation_count == sim->config.number_of_compiles_required)
			conct++;
		else
		{
			start_coder_compilation_cycle(coder);
			pthread_mutex_lock(&coder->mutex_cond.mutex);
			coder->has_dongle = true;
			pthread_cond_broadcast(&coder->mutex_cond.cond);
			pthread_mutex_unlock(&coder->mutex_cond.mutex);
		}
	}
	watcher_stop_monitor(sim);
	watcher_stop_coders(sim);
	printf("sssss\n");
}
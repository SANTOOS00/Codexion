/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:30:25 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/17 22:24:00 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"


bool	is_burnout	(t_simulation *sim)
{
	bool	check;

	pthread_mutex_lock(&sim->burnout_mutex);
	check = sim->is_burnout;
	pthread_mutex_unlock(&sim->burnout_mutex);
	return (check);
}



void start_coder_compilation_cycle(t_coder *coder)
{
	coder->compilation_count++;
	pick_up_dongle(coder);
	update_burnout_timer(coder);
}


void	run_fifo_routine(t_simulation *sim)
{
	t_coder	*coder;
	int		*i;
	int		conct;

	conct = 0;
	while (get_watcher_status(sim) != FINISHED_W)
	{
		if (is_burnout(sim) || conct == sim->config.number_of_coders)
			break ;
		coder = pop_queue_fifo(sim->queue);
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
}

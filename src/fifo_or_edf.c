/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo_or_edf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:30:25 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/22 00:42:20 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	start_coder_compilation_cycle(t_coder *coder)
{
	coder->compilation_count++;
	pick_up_dongle(coder);
	update_burnout_timer(coder);
}

void	watcher_stop_monitor_and_coders(t_simulation *sim)
{
	watcher_stop_monitor(sim);
	watcher_stop_coders(sim);
}

bool	mark_coder_finished_if_done(t_coder *coder,
			t_simulation *sim)
{
	if (coder->compilation_count
		== sim->config.number_of_compiles_required)
	{
		pthread_mutex_lock(&coder->mutex_cond.mutex);
		coder->status = FINISHED;
		pthread_mutex_unlock(&coder->mutex_cond.mutex);
		return (true);
	}
	return (false);
}

void	wait_watcher_nans(t_simulation *sim)
{
	struct timespec	time;

	time.tv_sec = 0;
	time.tv_nsec = 200;
	pthread_mutex_lock(&sim->monitor_mu_cond.mutex);
	pthread_cond_timedwait(&sim->monitor_mu_cond.cond,
		&sim->monitor_mu_cond.mutex, &time);
	pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
}

void	run_fifo_or_edf_routine(t_simulation *sim)
{
	int			nbfinicoders;
	t_coder		*coder;

	nbfinicoders = 0;
	while (get_watcher_status(sim) != FINISHED_W)
	{
		if (nbfinicoders == sim->config.number_of_coders)
			break ;
		coder = pop_queue(sim, sim->config.scheduler);
		if (!coder)
			wait_watcher_nans(sim);
		else if (mark_coder_finished_if_done(coder, sim))
			nbfinicoders++;
		else
		{
			start_coder_compilation_cycle(coder);
			pthread_mutex_lock(&coder->mutex_cond.mutex);
			coder->has_dongle = true;
			pthread_cond_broadcast(&coder->mutex_cond.cond);
			pthread_mutex_unlock(&coder->mutex_cond.mutex);
		}
	}
	if (get_watcher_status(sim) != IS_BURNOUT_W)
		watcher_stop_monitor_and_coders(sim);
}

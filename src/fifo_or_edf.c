/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo_or_edf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:30:25 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/20 04:53:34 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	start_coder_compilation_cycle(t_coder *coder)
{
	coder->compilation_count++;
	pick_up_dongle(coder);
	update_burnout_timer(coder);
}

bool	set_coder_finished(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	coder->status = FINISHED;
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
	return (true);
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
		set_coder_finished(coder);
		return (true);
	}
	return (false);
}

void	run_fifo_or_edf_routine(t_simulation *sim)
{
	int			number_of_finished_coders;
	t_coder		*coder;

	number_of_finished_coders = 0;
	while (get_watcher_status(sim) != FINISHED_W)
	{
		if (number_of_finished_coders == sim->config.number_of_coders)
			break ;
		coder = pop_queue(sim, sim->config.scheduler);
		if (!coder)
			usleep(10);
		else if (mark_coder_finished_if_done(coder, sim))
			number_of_finished_coders++;
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

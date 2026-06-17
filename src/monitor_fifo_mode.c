/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_fifo_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:30:25 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/17 21:20:56 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

t_monitor_status	check_status_monitor(t_simulation *sim)
{
	t_monitor_status	check_status;

	pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
	check_status = sim->monitor_status;
	pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
	return (check_status);
}

bool	check_burnout(t_simulation *sim)
{
	bool	check;

	pthread_mutex_lock(&sim->burnout_mutex);
	check = sim->is_burnout;
	pthread_mutex_unlock(&sim->burnout_mutex);
	return (check);
}

void	monitor_wake_coders(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		pthread_mutex_lock(&sim->coders[i]->mutex_cond.mutex);
		sim->coders[i]->status = FINISHED;
		sim->coders[i]->has_dongle = true;
		pthread_cond_broadcast(&sim->coders[i]->mutex_cond.cond);
		pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);
		i++;
	}
}

void	run_fifo_routine(t_simulation *sim)
{
	t_coder	*coder;
	int		*i;
	int		conct;

	conct = 0;
	coder = NULL;
	i = NULL;
	while (check_status_monitor(sim) != FINISHED_M)
	{
		if (check_burnout(sim) || conct == sim->config.number_of_coders)
		{
			
		}
			break ;
		coder = pop_queue_fifo(sim->queue);
		if (!coder)
			usleep(500);
		else if (coder->compilation_count == sim->config.number_of_compiles_required)
			conct++;
		else
		{
			coder->compilation_count++;
			printf("coder %d complinge %d \n", coder->id, coder->compilation_count);
			pick_up_dongle(coder);
			update_burnout_timer(coder, sim->config);
			pthread_mutex_lock(&coder->mutex_cond.mutex);
			coder->has_dongle = true;
			pthread_cond_broadcast(&coder->mutex_cond.cond);
			pthread_mutex_unlock(&coder->mutex_cond.mutex);
		}
	}
}

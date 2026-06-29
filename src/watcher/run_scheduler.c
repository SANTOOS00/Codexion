/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_scheduler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 03:28:54 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/29 12:44:22 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static bool	ft_check_is_finished_coder(t_simulation *sim, t_coder *coder);
static void	update_burnout_timer(t_coder *coder);
static void	ft_increment_compilation_counter(t_coder *coder);


bool test_name(t_simulation *sim)
{
	if(sim->finished_coders == sim->config.number_of_coders)
		return (false);
	return (true);
}
void	run_scheduler_loop(t_simulation *sim)
{
	t_coder	*coder;

	while (test_name(sim))
	{
		coder = pop_queue(sim, sim->config.scheduler);
		if (!coder)
			usleep(300);
		else if (ft_check_is_finished_coder(sim, coder))
			continue ;
		else
		{
			pick_up_dongle(coder);
			update_burnout_timer(coder);
			pthread_mutex_lock(&coder->mutex_cond.mutex);
			coder->has_dongle = true;
			pthread_cond_broadcast(&coder->mutex_cond.cond);
			pthread_mutex_unlock(&coder->mutex_cond.mutex);
			ft_increment_compilation_counter(coder);
		}
	}
	ft_stop_simulation(sim);
	printf("ssss\n");
}

static bool	ft_check_is_finished_coder(t_simulation *sim, t_coder *coder)
{
	bool	is_check;

	is_check = false;
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	if (coder->compilation_count >= coder->config->number_of_compiles_required)
	{
		is_check = true;
		coder->has_dongle = true;
		coder->status = FINISHED;
		pthread_cond_broadcast(&coder->mutex_cond.cond);
	}
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
	if (is_check)
	{
		pthread_mutex_lock(&sim->finished_coders_m);
		sim->finished_coders++;
		pthread_mutex_unlock(&sim->finished_coders_m);
	}
	return (is_check);
}

static void	update_burnout_timer(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	coder->deadline = get_time() + coder->config->time_to_burnout;
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

static void	ft_increment_compilation_counter(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	coder->compilation_count++;
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

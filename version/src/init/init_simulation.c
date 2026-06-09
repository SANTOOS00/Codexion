/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:59:05 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/05 17:58:41 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	clean_mutex_cond_simulation(t_simulation *simulation)
{
	pthread_mutex_destroy(&simulation->burnout_mutex);
	destroy_mutex_cond(&simulation->coders_cnt_lock);
	destroy_mutex_cond(&simulation->watch_lock);
	destroy_mutex_prints(simulation);
}

bool	init_mutex_prints(t_simulation *sim)
{
	if (pthread_mutex_init(&sim->mutex_print, NULL) != 0)
		return (false);
	return (true);
}

bool	ft_set_simulation_intial_state(int argc, char **argv,
		t_simulation *simulation)
{
	reset_simulation_vars(simulation);
	if (parse_args(argc, argv, simulation) == false)
		return (false);
	if (init_mutex_cond(&simulation->coders_cnt_lock) == false)
		return (false);
	if (init_mutex_cond(&simulation->watch_lock) == false)
	{
		destroy_mutex_cond(&simulation->coders_cnt_lock);
		return (false);
	}
	if (pthread_mutex_init(&simulation->burnout_mutex, NULL) != 0)
	{
		destroy_mutex_cond(&simulation->coders_cnt_lock);
		destroy_mutex_cond(&simulation->watch_lock);
		return (false);
	}
	if (init_mutex_prints(simulation) == false)
	{
		destroy_mutex_cond(&simulation->coders_cnt_lock);
		destroy_mutex_cond(&simulation->watch_lock);
		pthread_mutex_destroy(&simulation->burnout_mutex);
		return (false);
	}
	return (true);
}

bool	init_queue_normal(t_simulation *simulation)
{
	if (ft_init_queue_normal(simulation) == false)
	{
		clean_coders(simulation->coders, simulation->config.number_of_coders);
		clean_dongles(simulation->dongles, simulation->config.number_of_coders);
		clean_queue(simulation->queue);
		clean_mutex_cond_simulation(simulation);
		return (false);
	}
	return (true);
}

bool	ft_init_simulation(int argc, char **argv, t_simulation *simulation)
{
	if (ft_set_simulation_intial_state(argc, argv, simulation) == false)
		return (false);
	if (init_coders(simulation) == false)
	{
		clean_mutex_cond_simulation(simulation);
		return (false);
	}
	if (alloc_and_init_dongles(simulation) == false)
	{
		clean_mutex_cond_simulation(simulation);
		clean_coders(simulation->coders, simulation->config.number_of_coders);
		return (false);
	}
	if (ft_init_queue(simulation) == false)
	{
		clean_coders(simulation->coders, simulation->config.number_of_coders);
		clean_dongles(simulation->dongles, simulation->config.number_of_coders);
		clean_mutex_cond_simulation(simulation);
		return (false);
	}
	if (init_queue_normal(simulation) == false)
		return (false);
	ft_set_coders_initial_state(simulation);
	return (true);
}

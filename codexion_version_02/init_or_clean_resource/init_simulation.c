/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:59:05 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/13 16:38:34 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"


void reset_simulation_vars(t_simulation *sim)
{
	sim->is_burnout = false;
	sim->run_coders_counter = 0;
	sim->is_watch_waiting = true;
	sim->monitor_status = START_M;
	sim->time_start = 0;
	sim->is_watch_waiting = false;
	sim->watch_status = START_W;
}


bool ft_set_simulation_intial_state(int argc, char **argv, t_simulation *simulation)
{
	reset_simulation_vars(simulation);
	if (parse_args(argc, argv, &simulation->config) == false)
		return (false);
	if (init_mutex_cond(&simulation->coders_cnt_lock) == false)
		return (false);
	if (init_mutex_cond(&simulation->watch_lock)== false)
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
	return (true);
}

bool ft_init_simulation(int argc, char **argv, t_simulation *simulation)
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
	}

	if(ft_init_coder_crossing(simulation)== false)
	{
		clean_coders(simulation->coders, simulation->config.number_of_coders);
		clean_dongles(simulation->dongles, simulation->config.number_of_coders);
		clean_queue(simulation->queue);
		clean_mutex_cond_simulation(simulation);
		return (false);
	}
	ft_set_coders_initial_state(simulation);
	return (true);	
}
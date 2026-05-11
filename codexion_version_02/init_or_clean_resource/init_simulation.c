/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:59:05 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/11 11:31:27 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"



void clean_mutex_cond_simulation(t_simulation *simulation)
{
	pthread_mutex_destroy(&simulation->burnout_mutex);
	destory_mutex_cond(&simulation->coders_cnt_lock);
	destory_mutex_cond(&simulation->monitor_wait_lock);
}


bool ft_set_simulation_intial_state(int argc, char **argv, t_simulation *simulation)
{
	simulation->is_burnout = false;
	simulation->run_coders_counter = 0;
	simulation->check_wait_monitor= true;
	simulation->monitor_status = START_M;
	if (parse_args(argc, argv, &simulation->config) == false)
		return (false);
	if (init_mutex_cond(&simulation->coders_cnt_lock) == false)
		return (false);
	if (init_mutex_cond(&simulation->monitor_wait_lock)== false)
	{
		destory_mutex_cond(&simulation->coders_cnt_lock);
		return (false);
	}
	if (pthread_mutex_init(&simulation->burnout_mutex, NULL) != 0)
	{
		destory_mutex_cond(&simulation->coders_cnt_lock);
		destory_mutex_cond(&simulation->monitor_wait_lock);
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

	if(ft_init_queue_fifo(simulation)== false)
	{
		clean_coders(simulation->coders, simulation->config.number_of_coders);
		clean_dongles(simulation->dongles, simulation->config.number_of_coders);
		clean_mutex_cond_simulation(simulation);
		clean_queue_pro(simulation->queue_priority);
		return (false);
	}
	ft_set_coders_initial_state(simulation);
	return (true);	
}
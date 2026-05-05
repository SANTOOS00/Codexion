/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:59:05 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/05 03:56:50 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



void clean_mutex_cond_simulation(t_simulation *simulation)
{
	pthread_mutex_destroy(&simulation->burnout_mutex);
	destory_mutex_cond(&simulation->coders_counter_m_c);
}


bool ft_set_simulation_intial_state(int argc, char **argv, t_simulation *simulation)
{
	
	if (parse_args(argc, argv, &simulation->config) == false)
		return (false);
	if (init_mutex_cond(&simulation->coders_counter_m_c) == false)
		return (false);
	if (pthread_mutex_init(&simulation->burnout_mutex, NULL) != 0)
	{
		destory_mutex_cond(&simulation->coders_counter_m_c);
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
		free_2d_array((void **)simulation->coders, simulation->config.number_of_coders);
		return (false);
	}
	ft_set_coders_initial_state(simulation);
	return (true);
		
}
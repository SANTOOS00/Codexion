/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:59:05 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/05 00:53:17 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



t_action init_simulation(t_simulation *simulation)
{
	if(init_mutex_cond(&simulation->coders_counter_m_c) == FAIL)
		return (FAIL);
	if (pthread_mutex_init(&simulation->burnout_mutex, NULL) != 0)
	{
		destory_mutex_cond(&simulation->coders_counter_m_c);
		return (FAIL);
	}		
	return (SUCCESS);
}


void destroy_m_c_simulation(t_simulation *simulation)
{
	destory_mutex_cond(&simulation->coders_counter_m_c);
	pthread_mutex_destroy(&simulation->burnout_mutex);
	free_2d_array((void **)simulation->coders, simulation->config.number_of_coders);
	
}

t_action ft_init_simulation(int argc, char **argv, t_simulation *simulation)
{
	if (parse_args(argc, argv, &simulation->config) == FAIL)
		return (FAIL);
	if (init_simulation(simulation) == FAIL)
		return (FAIL);
	if (init_coders(simulation) == FAIL)
	{
		destroy_m_c_simulation(simulation);
		return (FAIL);
	}
	if (alloc_and_init_dongles(simulation) == FAIL)
	{
		destroy_m_c_simulation(simulation);
		return (FAIL);
	}
	if (ft_set_coders_initial_state(simulation) == FAIL)
	{
		clean_resource(simulation);
		return (FAIL); 
	}
	
	return (SUCCESS);
		
}
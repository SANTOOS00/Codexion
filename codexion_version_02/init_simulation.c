/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:59:05 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/04 20:15:33 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


void destory_mutex_cond(t_mutex_cond *mutex_cond)
{
	pthread_mutex_destroy(&mutex_cond->mutex);
	pthread_cond_destroy(&mutex_cond->cond);
}

t_action init_mutex_cond(t_mutex_cond *mutex_cond)
{
	if (pthread_mutex_init(&mutex_cond->mutex, NULL) != 0)
		return (fail);
	if (pthread_cond_init(&mutex_cond->cond, NULL) != 0)
	{
		pthread_mutex_destroy(&mutex_cond->mutex);
		return (fail);
	}
	return (success);
}

t_action init_simulation(t_simulation *simulation)
{
	if(init_mutex_cond(&simulation->coders_counter_m_c) == fail)
		return (fail);
	if (pthread_mutex_init(&simulation->burnout_mutex, NULL) != 0)
	{
		destory_mutex_cond(simulation->coders_counter);
		return (fail);
	}		
	return (success);
}


void destroy_m_c_simulation(t_simulation *simulation)
{
	destory_mutex_cond(&simulation->coders_counter_m_c);
	pthread_mutex_destroy(&simulation->burnout_mutex);
	
}

t_action ft_init_simulation(int argc, char **argv, t_simulation *simulation)
{
	if (parse_args(argc, argv, &simulation->config) == fail)
		return (fail);
	if (init_simulation(simulation) == fail)
		return (fail);
	if (init_coders(simulation) == fail)
	{
		destroy_m_c_simulation(simulation);
		return (fail);
	}
	if (alloc_and_init_dongles(simulation) == fail)
	{
		destroy_m_c_simulation(simulation);
		return (fail);
	}
	return (success);
		
}
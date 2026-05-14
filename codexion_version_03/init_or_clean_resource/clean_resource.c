/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_resource.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 04:05:58 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/14 15:46:28 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"



void destroy_mutex_cond(t_mutex_cond *mutex_cond)
{
	pthread_mutex_destroy(&mutex_cond->mutex);
	pthread_cond_destroy(&mutex_cond->cond);
}


void clean_mutex_cond_simulation(t_simulation *simulation)
{
	pthread_mutex_destroy(&simulation->burnout_mutex);
	destroy_mutex_cond(&simulation->monitor_lock);
	destroy_mutex_cond(&simulation->watch_lock);
}


void clean_dongles(t_dongle **dongles, int size)
{
	clean_mutex_dongles(dongles, size);
	free_2d_array((void **)dongles, size);
}

void clean_coders(t_coder **coders, int size)
{
	destroy_mutex_cond_coders(coders, size);
	free_2d_array((void **)coders, size);
}


void clean_resource(t_simulation *simulation)
{
	clean_dongles(simulation->dongles, simulation->config.number_of_coders);
	clean_coders(simulation->coders, simulation->config.number_of_coders);
	clean_queue(simulation->queue);
	clean_crossing(simulation->crossing);
	clean_mutex_cond_simulation(simulation);
}

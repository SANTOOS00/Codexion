/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_resource.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 22:18:53 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/27 12:44:09 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	destroy_mutex_cond(t_mutex_cond *mutex_cond)
{
	pthread_mutex_destroy(&mutex_cond->mutex);
	pthread_cond_destroy(&mutex_cond->cond);
}

void	clean_dongles(t_dongle **dongles, int size)
{
	clean_mutex_dongles(dongles, size);
	ft_free_double_array((void **)dongles, size);
}

void	clean_coders(t_coder **coders, int size)
{
	destroy_mutex_cond_coders(coders, size);
	ft_free_double_array((void **)coders, size);
}

void	clean_queue(t_queue *queue)
{
	pthread_mutex_destroy(&queue->mutex_queue);
	free(queue->coders);
	free(queue);
}

void	ft_clean_resource(t_simulation *simulation)
{
	clean_dongles(simulation->dongles, simulation->config.number_of_coders);
	clean_coders(simulation->coders, simulation->config.number_of_coders);
	clean_queue(simulation->queue);
	clean_mutex_cond_simulation(simulation);
}

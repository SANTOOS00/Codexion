/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:24:44 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/22 16:42:09 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	clean_queue(t_queue *queue)
{
	pthread_mutex_destroy(&queue->mutex_queue);
	free(queue->coders);
	free(queue);
}

bool	ft_init_queue(t_simulation *sim)
{
	t_queue	*queue;

	queue = (t_queue *)malloc(sizeof(t_queue));
	if (!queue)
		return (false);
	if (pthread_mutex_init(&queue->mutex_queue, NULL) != 0)
		return (free(queue), false);
	queue->coders = (t_coder **)malloc(sizeof(t_coder *)
			* sim->config.number_of_coders);
	if (!queue->coders)
	{
		pthread_mutex_destroy(&queue->mutex_queue);
		return (free(queue), false);
	}
	queue->capacity = sim->config.number_of_coders;
	queue->size = 0;
	sim->queue = queue;
	return (true);
}

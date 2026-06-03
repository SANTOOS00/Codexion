/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:24:44 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/02 21:48:23 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	clean_queue(t_queue *queue)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&queue->mutex_queue);
	while (i < queue->capacity)
		free(queue->heap[i++]);
	free(queue->heap);
	free(queue);
}

bool	ft_init_queue(t_simulation *sim)
{
	t_queue	*queue;
	int		i;
	int		j;

	j = 0;
	i = 0;
	queue = (t_queue *)malloc(sizeof(t_queue));
	if (!queue)
		return (false);
	if (pthread_mutex_init(&queue->mutex_queue, NULL) != 0)
		return (free(queue), false);
	queue->heap = (t_dongle_request **)malloc(sizeof(t_dongle_request *)
			* sim->config.number_of_coders);
	if (!queue->heap)
		return (free(queue), false);
	while (i < sim->config.number_of_coders)
	{
		queue->heap[i] = (t_dongle_request *)malloc(sizeof(t_dongle_request));
		if (!queue->heap[i])
		{
			while (j < i)
				free(queue->heap[j++]);
			free(queue->heap);
			free(queue);
			return (false);
		}
		i++;
	}
	queue->capacity = sim->config.number_of_coders;
	queue->time_burnout = sim->config.time_to_burnout;
	queue->size = 0;
	sim->queue = queue;
	return (true);
}

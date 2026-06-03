/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:47:02 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/02 21:48:15 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	clean_queue_normal(t_queue_normal *queue_normal)
{
	pthread_mutex_destroy(&queue_normal->mutex_crossing);
	free(queue_normal->heap);
	free(queue_normal);
}

static void	free_2d_arrays(t_coder **heap, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(heap[i++]);
	free(heap);
}

t_queue_normal	*alloc_queue_normal(int coders_number)
{
	t_queue_normal	*queue_normal;

	queue_normal = (t_queue_normal *)malloc(sizeof(t_queue_normal));
	if (!queue_normal)
		return (NULL);
	queue_normal->heap = (t_coder **)malloc(sizeof(t_coder *) * coders_number);
	if (!queue_normal->heap)
	{
		free(queue_normal);
		return (NULL);
	}
	queue_normal->size = 0;
	queue_normal->capacity = coders_number;
	return (queue_normal);
}

bool	ft_init_queue_normal(t_simulation *sim)
{
	t_queue_normal *queue_normal;

	queue_normal = alloc_queue_normal(sim->config.number_of_coders);
	if (!queue_normal)
		return (false);
	if (pthread_mutex_init(&queue_normal->mutex_crossing, NULL) != 0)
	{
		free_2d_array((void **)queue_normal->heap, queue_normal->capacity);
		free(queue_normal);
		return (false);
	}
	queue_normal->capacity = sim->config.number_of_coders;
	queue_normal->size = 0;
	sim->queue_normal = queue_normal;
	return (true);
}
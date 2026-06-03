/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_normal_manager.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 16:15:36 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/02 22:15:57 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

t_coder	*pop_queue_normal(t_queue_normal *queue_normal)
{
	t_coder	*coder;
	int		i;

	pthread_mutex_lock(&queue_normal->mutex_crossing);
	coder = queue_normal->heap[0];
	i = 1;
	while (queue_normal->size > i)
	{
		queue_normal->heap[i - 1] = queue_normal->heap[i];
		i++;
	}
	queue_normal->size--;
	pthread_mutex_unlock(&queue_normal->mutex_crossing);
	return (coder);
}

void	add_queue_normal_to_queue(t_queue_normal *queue_normal, t_queue *queue,
		t_scheduler scheduler)
{
	t_coder	*coder;
	int		size_queue_normal;

	pthread_mutex_lock(&queue_normal->mutex_crossing);
	size_queue_normal = queue_normal->size;
	pthread_mutex_unlock(&queue_normal->mutex_crossing);
	while (size_queue_normal)
	{
		coder = pop_queue_normal(queue_normal);
		push_to_priority_queue(queue, coder, scheduler);
		size_queue_normal--;
	}
}

void	push_normal_queue(t_coder *coder)
{
	t_queue_normal *queue_normal;

	queue_normal = coder->queue_normal;
	pthread_mutex_lock(&queue_normal->mutex_crossing);
	queue_normal->heap[queue_normal->size] = coder;

	queue_normal->size++;
	pthread_mutex_unlock(&queue_normal->mutex_crossing);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_pop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 02:40:19 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/24 05:10:38 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

t_coder	*pop_queue_fifo(t_queue *q);
bool	is_valid_dongl_left_right(t_coder *coder);


t_coder	*pop_queue(t_simulation *sim, t_scheduler scheduler)
{
	t_coder		*coder;

	coder = NULL;
	pthread_mutex_lock(&sim->queue->mutex_queue);
	if (sim->queue->size <= 0)
	{
		
		pthread_mutex_unlock(&sim->queue->mutex_queue);
		return (NULL);
	}
	if (scheduler == FIFO)
		coder = pop_queue_fifo(sim->queue);
	else
	{
		// if (!is_valid_dongl_left_right(sim->queue->coders[0]))
		// 	move_first_valid_coder_to_front(sim->queue);
		coder = pop_queue_edf(sim->queue);
	}
	pthread_mutex_unlock(&sim->queue->mutex_queue);
	return (coder);
}

void	push_priority_queue(t_coder *coder)
{
	t_queue	*queue;

	queue = coder->queue;
	queue->coders[queue->size] = coder;
	if (coder->config->scheduler == EDF)
		heapify_up(queue, queue->size);
	queue->size++;
}

t_coder	*pop_queue_edf(t_queue *q)
{
	t_coder		*coder;
	int i;

	i = 0;
	coder = NULL;
	if (q->size == 0)
		return (NULL);
	while (i < q->size)
	{
		if (is_valid_dongl_left_right(q->coders[i]))
		{
			coder = q->coders[0];
			q->coders[0] = q->coders[q->size - 1];
			heapify_down(q, 0);                                              
			q->size--;
			return (coder);
		}
		i++;
	}
	return (coder);
}

void	move_first_valid_coder_to_front(t_queue *q)
{
	int		parent;
	int		child_left;
	int		child_right;
	int		tmp;

	parent = 0;
	tmp = 0;
	
	if (q->size < 3)
		return;
	
	child_left = child_left_index(parent);
	child_right = child_right_index(parent);
	if (is_same_comp(q->coders[child_right], q->coders[parent])
		&& is_valid_dongl_left_right(q->coders[child_right]))
		tmp = child_right;
	if (is_same_comp(q->coders[child_left], q->coders[parent])
		&& is_valid_dongl_left_right(q->coders[child_left]))
		tmp = child_left;
	if (tmp == parent)
		return ;
	ft_swap(&q->coders[tmp], &q->coders[parent]);
	return ;
}

void	shift_queue_elements(t_queue *q)
{
	int	i;

	i = 1;
	while (i < q->size)
	{
		q->coders[i - 1] = q->coders[i];
		i++;
	}
}


t_coder	*pop_queue_fifo(t_queue *q)
{
	t_coder	*coder;

	coder = NULL;
	coder = q->coders[0];
	if (!is_valid_dongl_left_right(q->coders[0]))
		return (NULL);
	shift_queue_elements(q);
	q->size--;
	return (coder);
}

bool	try_take_dongle(t_dongle *dongle)
{
	bool	success;

	pthread_mutex_lock(&dongle->mutex);
	success = false;
	if (dongle->is_available 
		&& get_time() - dongle->last_release_time >= dongle->cooldown_time)
		success = true;
	pthread_mutex_unlock(&dongle->mutex);
	return (success);
}

bool	is_valid_dongl_left_right(t_coder *coder)
{
	return (try_take_dongle(coder->left_dongle)
		&& try_take_dongle(coder->right_dongle));
}
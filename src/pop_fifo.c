/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_fifo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:16:29 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/13 18:15:11 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

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
	if (q->capacity == 1)
		return (NULL);
	pthread_mutex_lock(&q->mutex_queue);
	coder = q->coders[0];
	if (!is_valid_dongl_left_right(q->coders[0]))
	{
		pthread_mutex_unlock(&q->mutex_queue);
		return (NULL);
	}
	shift_queue_elements(q);
	q->size--;
	pthread_mutex_unlock(&q->mutex_queue);
	return (coder);
}

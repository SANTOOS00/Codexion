/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_edf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:29:30 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/13 18:15:14 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

t_coder	*pop_queue_edf(t_queue *q)
{
	int		i;
	int		best;
	t_coder	*coder;

	best = -1;
	i = 0;
	pthread_mutex_lock(&q->mutex_queue);
	while (i < q->size)
	{
		if (is_valid_dongl_left_right(q->coders[i]))
		{
			if (best == -1 || is_greater(q->coders[i], q->coders[best]))
				best = i;
		}
		i++;
	}
	if (best == -1)
	{
		pthread_mutex_unlock(&q->mutex_queue);
		return (NULL);
	}
	coder = q->coders[best];
	q->coders[best] = q->coders[q->size - 1];
	q->size--;
	heapify_up(q, best);
	pthread_mutex_unlock(&q->mutex_queue);
	return (coder);
}
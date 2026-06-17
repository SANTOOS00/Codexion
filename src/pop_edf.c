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
	t_coder	*coder;

	pthread_mutex_lock(&q->mutex_queue);
	if (q->size == 0)
	{
		pthread_mutex_unlock(&q->mutex_queue);
		return (NULL);
	}
	if (is_valid_dongl_left_right(q->coders[0]))
	{
		coder = q->coders[0];
		q->coders[0] = q->coders[q->size - 1];
		q->size--;
		heapify_down(q, 0);
		pthread_mutex_unlock(&q->mutex_queue);
		return (coder);
	}
	pthread_mutex_unlock(&q->mutex_queue);
	return (NULL);
		

}
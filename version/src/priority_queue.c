/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 17:20:51 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/05 19:01:05 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

t_coder	*pop_queue(t_queue *q, t_scheduler scheduler)
{
	t_coder	*coder;
	int		i;

	coder = NULL;
	i = 1;
	pthread_mutex_lock(&q->mutex_queue);
	if (q->size == 0)
	{
		pthread_mutex_unlock(&q->mutex_queue);
		return (NULL);
	}
	coder = pop_edf_or_fifo(q, scheduler);
	pthread_mutex_unlock(&q->mutex_queue);
	return (coder);
}

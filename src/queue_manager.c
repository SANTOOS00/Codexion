/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 02:40:02 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/20 04:53:10 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

t_coder	*pop_queue(t_simulation *sim, t_scheduler scheduler)
{
	t_coder		*coder;

	coder = NULL;
	if (1 == sim->queue->capacity)
		return (NULL);
	pthread_mutex_lock(&sim->queue->mutex_queue);
	if (scheduler == FIFO)
		coder = pop_queue_fifo(sim->queue);
	else
	{
		move_first_valid_coder_to_front(sim->queue);
		coder = pop_queue_edf(sim->queue);
	}
	pthread_mutex_unlock(&sim->queue->mutex_queue);
	return (coder);
}
	
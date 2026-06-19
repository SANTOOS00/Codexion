/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 03:01:48 by santoos           #+#    #+#             */
/*   Updated: 2026/06/19 03:01:49 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

t_coder	*pop_queue(t_simulation *sim, t_scheduler scheduler)
{
	t_coder		*coder;

	coder = NULL;
	pthread_mutex_lock(&sim->queue->mutex_queue);
	if (scheduler == FIFO)
		coder = pop_queue_fifo(sim->queue);
	else
	{
		move_first_valid_coder_to_front(sim->queue, 0);
		coder = pop_queue_edf(sim->queue);
	}
	pthread_mutex_unlock(&sim->queue->mutex_queue);
	return (coder);
}

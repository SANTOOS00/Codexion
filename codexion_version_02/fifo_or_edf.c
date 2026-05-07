/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo_or_edf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:50:54 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/07 10:13:17 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


bool ft_edf(t_simulation *sim)
{
	
	return (true);
}


bool ft_fifo(t_simulation *sim)
{
	int i;

	i = 0;
	pthread_mutex_lock(&sim->queue->mutex);
	while (i < sim->queue->size)
	{
		printf("id coder %d pointeur %p  || time %lld\n", sim->queue->heap[i]->coder->id, sim->queue->heap[i]->coder, sim->queue->heap[i]->deadline);
		i++;
	}
	pthread_mutex_unlock(&sim->queue->mutex);
	return (true);
}


bool ft_fifo_or_edf(t_simulation *sim)
{
	if (sim->config.scheduler == FIFO)
		ft_fifo(sim);
	else if(sim->config.scheduler == EDF)
		ft_edf(sim);
	return (true);
}

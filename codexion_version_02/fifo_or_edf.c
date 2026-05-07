/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo_or_edf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:50:54 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/07 17:34:41 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int index_parent(int i)
{
	return (i - 1 / 2);
}

void ft_swap(t_dongle_request **arg1, t_dongle_request **arg2)
{
	t_dongle_request *timp;
	timp = *arg1;
	*arg1 = *arg2;
	*arg2 = timp;
}

void notify_monitor_push(t_queue *queue)
{
	int i;
	
	pthread_mutex_lock(&queue->mutex);
	i = queue->size;
	while(i > 0 && queue->heap[i]->deadline < queue->heap[index_parent(i)]->deadline)
	{
		printf("sss\n");
		ft_swap(&queue->heap[i], &queue->heap[index_parent(i)]);
		i = index_parent(i);
	}
	pthread_mutex_unlock(&queue->mutex);
	return ;
}

bool ft_edf(t_simulation *sim)
{
	while (1)
	{
		pthread_mutex_lock(&sim->monitor_wait_lock.mutex);
		while (sim->check_wait_monitor)
		{
			printf("sss\n");
			pthread_cond_wait(&sim->monitor_wait_lock.cond, &sim->monitor_wait_lock.mutex);
		}
		pthread_mutex_unlock(&sim->monitor_wait_lock.mutex);
		// notify_monitor_push(sim->queue);
	}
	return (true);
}


bool ft_fifo(t_simulation *sim)
{
	return (true);
}


bool ft_fifo_or_edf(t_simulation *sim)
{
	if (sim->config.scheduler == FIFO)
		ft_fifo(sim);
	else if(sim->config.scheduler == EDF)
	{
		printf("sss\n");
		ft_edf(sim);
	}
	return (true);
}

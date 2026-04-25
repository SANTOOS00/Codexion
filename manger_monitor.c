/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manger_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 21:29:02 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/25 14:53:55 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"







void *manger_monitor(void *arg)
{
	t_queue **queue;
	t_monitor *monitor;
	monitor = (t_monitor *)arg;
	int i = 0;
	printf("%p \n", queue);
	// printf("%p \n", queue);
	// printf("%p \n", queue);
	pthread_mutex_lock(monitor->mutex);
	queue = get_or_create_queue(0);
	pthread_mutex_unlock(monitor->mutex);
	while(queue[i])
	{
		printf("pointeur %d => %p\n", queue[i]->coder->id, queue[i]);
		i++;
	}
	if (monitor->config.scheduler == FIFO)
		ft_fifo(queue, monitor->config);
	if (monitor->config.scheduler == FIFO)
		ft_edf(queue, monitor->config);
	return NULL;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manger_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 21:29:02 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/28 13:31:22 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"




// void time_coder_init(t_queue **queue)
// {
	
// }


void *manger_monitor(void *arg)
{
	struct timeval new;
	int i;
	i = 0;
	gettimeofday(&new, NULL);
	t_queue **queue;
	t_monitor *monitor;
	monitor = (t_monitor *)arg;
	pthread_mutex_lock(monitor->mutex);
	queue = get_or_create_queue(0);
	printf("%ld\n", new.tv_sec);
	while(queue[i])
	    queue[i++]->coder->time_coder = new;
	pthread_mutex_unlock(monitor->mutex);
	if (monitor->config.scheduler == FIFO)
		ft_fifo(queue, monitor->config);
	if (monitor->config.scheduler == EDF)
		ft_edf(queue, monitor->config);
	return NULL;
}
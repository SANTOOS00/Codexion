/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_tid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 16:17:56 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/14 15:48:06 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


void *watcher_tid_routine(void *arg)
{
	t_simulation *sim;
	
	sim = (t_simulation *)arg; 
	pthread_mutex_lock(&sim->watch_lock.mutex);
	while (!sim->is_watch_waiting)
		pthread_cond_wait(&sim->watch_lock.cond, &sim->watch_lock.mutex);
	if (sim->watch_status == ERROR_W)
		return (NULL);
	pthread_mutex_unlock(&sim->watch_lock.mutex);
    printf("is watcher_tid_routine ok\n");
	return (NULL);
}
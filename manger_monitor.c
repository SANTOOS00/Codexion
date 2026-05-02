/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manger_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 21:29:02 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/28 15:16:27 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void *manger_monitor(void *arg)
{
	t_monitor *monitor;

	monitor = (t_monitor *)arg;
	pthread_mutex_lock(&monitor->mutex);
	while(monitor->cheack)
		pthread_cond_wait(&monitor->cond, &monitor->mutex);
	pthread_mutex_unlock(&monitor->mutex);
	printf("sims");
	return NULL;
}
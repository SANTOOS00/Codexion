/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_coders_and_watcher.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 21:06:44 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/13 18:35:45 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	watcher_wake_monitor(t_simulation *sim)
{
	pthread_mutex_lock(&sim->watch_lock.mutex);
	sim->is_watch_waiting = true;
	pthread_cond_broadcast(&sim->watch_lock.cond);
	pthread_mutex_unlock(&sim->watch_lock.mutex);
}
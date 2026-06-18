/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wake_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 21:06:44 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/18 08:01:04 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	watcher_wake_monitor(t_simulation *sim)
{
	pthread_mutex_lock(&sim->monitor_mu_cond.mutex);
	sim->is_watch_waiting = true;
	pthread_cond_broadcast(&sim->monitor_mu_cond.cond);
	pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
}

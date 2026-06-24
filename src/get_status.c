/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 08:03:18 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/24 04:35:28 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

t_watch_status	get_watcher_status(t_simulation *sim)
{
	t_watch_status	check_status;

	pthread_mutex_lock(&sim->watch_mu_cond.mutex);
	check_status = sim->watch_status;
	pthread_mutex_unlock(&sim->watch_mu_cond.mutex);
	return (check_status);
}

t_coder_status	get_status_coder(t_coder *coder)
{
	t_coder_status	status;

	pthread_mutex_lock(&coder->mutex_cond.mutex);
	status = coder->status;
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
	return (status);
}

t_monitor_status	get_status_monitor(t_simulation *sim)
{
	t_monitor_status	status;

	pthread_mutex_lock(&sim->monitor_mu_cond.mutex);
	status = sim->monitor_status;
	pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
	return (status);
}

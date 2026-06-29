/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 04:52:11 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/28 23:44:06 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

t_watch_status	ft_get_status_watcher(t_simulation *sim)
{
	t_watch_status	status;

	pthread_mutex_lock(&sim->watch_mu_cond.mutex);
	status = sim->watch_status;
	pthread_mutex_unlock(&sim->watch_mu_cond.mutex);
	return (status);
}

// void	ft_stop_simulation(t_simulation *sim)
// {
// 	int i;

// 	i  = 0;
// 	while (i < sim->config.number_of_coders)
// 	{
// 		pthread_mutex_lock(&sim->coders[i]->mutex_cond.mutex);
// 		sim->coders[i]->has_dongle = true;
// 		if (sim->coders[i]->is_waiting_coder)
// 			pthread_cond_broadcast(&sim->coders[i]->mutex_cond.cond);
// 		pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);
// 	}
// }
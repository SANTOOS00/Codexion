/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 04:52:11 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/29 03:49:19 by santoos          ###   ########.fr       */
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

void	ft_stop_simulation(t_simulation *sim)
{
	pthread_mutex_lock(&sim->is_finished_sim_m);
	sim->is_finished_sim = true;
	pthread_mutex_unlock(&sim->is_finished_sim_m);
}
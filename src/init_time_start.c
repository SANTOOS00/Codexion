/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_time_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 18:55:49 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/18 07:50:48 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	set_simulation_start_time(t_simulation *sim)
{
	pthread_mutex_lock(&sim->monitor_mu_cond.mutex);
	sim->time_start = get_time();
	pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
}

void	initialize_start_time(t_simulation *sim)
{
	set_simulation_start_time(sim);
}

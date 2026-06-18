/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_time_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 18:55:49 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/17 20:21:53 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"


void	set_simulation_start_time(t_simulation *sim)
{
	pthread_mutex_lock(&sim->monitor_mu_cond.mutex);
	sim->time_start = get_time();
	pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
}

void init_coders_deadlines(t_simulation *sim)
{
	int i;

	i = 0;
	while(i < sim->config.number_of_coders)
		sim->coders[i++]->deadline = sim->config.time_to_burnout + get_time();
} 


void init_time_start(t_simulation *sim)
{
    init_coders_deadlines(sim);
    set_simulation_start_time(sim);
}
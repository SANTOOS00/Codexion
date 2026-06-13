/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_fifo_or_edf_mode.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 22:12:53 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/13 18:11:21 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void init_time_start_coders(t_simulation *sim)
{
	int i;

	i = 0;
	while(i < sim->config.number_of_coders)
		sim->coders[i++]->deadline = sim->config.time_to_burnout + get_time();
} 

void	run_fifo_or_edf_routine(t_simulation *sim)
{
	init_time_start_coders(sim);
	if (sim->config.scheduler == FIFO)
		run_fifo_routine(sim);
	else if (sim->config.scheduler == EDF)
		run_edf_routine(sim);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_simulation_vars.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:42:43 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/05 17:48:24 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	reset_simulation_vars(t_simulation *sim)
{
	sim->is_burnout = false;
	sim->run_coders_counter = 0;
	sim->is_watch_waiting = true;
	sim->monitor_status = START_M;
	sim->time_start = 0;
	sim->is_watch_waiting = false;
	sim->watch_status = START_W;
}

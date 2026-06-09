/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_simulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:37:59 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/06 03:19:24 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

bool	create_coders(t_simulation *sim)
{
	int	i;
	int	ret;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		ret = pthread_create(&sim->coders[i]->thread,
				NULL, coder_routine, sim->coders[i]);
		if (ret != 0)
		{
			fprintf(stderr,
				"Error: pthread_create failed: %s\n",
				strerror(ret));
			fprintf(stderr,
				"id coder failed %d\n", i);
			exit_coders(sim, i);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	start_simulation(t_simulation *sim)
{
	if (pthread_create(&sim->monitor_tid, NULL, monitor_routine, sim) != 0)
		return (false);
	if (pthread_create(&sim->watcher_tid, NULL, watcher_routine, sim) != 0)
	{
		exit_monitor(sim);
		return (false);
	}
	if (create_coders(sim) == false)
	{
		exit_monitor(sim);
		exit_watcher(sim);
		return (false);
	}
	return (true);
}

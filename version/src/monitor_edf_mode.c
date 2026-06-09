/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_edf_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 21:58:28 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/07 04:21:50 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

// bool	size_queue_normal(t_queue_normal *q)
// {
// 	int	size;

// 	pthread_mutex_lock(&q->mutex_crossing);
// 	size = q->size;
// 	pthread_mutex_unlock(&q->mutex_crossing);
// 	return (size > 0);
// }

void	run_edf_routine(t_simulation *sim)
{
	t_coder	*coder;

	while (check_status_monitor(sim) != FINISHED_M)
	{
		// add_queue_normal_to_queue(sim->queue_normal, sim->queue, EDF);
		if (check_burnout(sim))
			break ;
		coder = pop_queue(sim->queue, EDF);
		if (!coder)
			usleep(500);
		else
		{
			pick_up_dongle(coder);
			pthread_mutex_lock(&coder->mutex_cond.mutex);
			coder->has_dongle = true;
			pthread_cond_broadcast(&coder->mutex_cond.cond);
			pthread_mutex_unlock(&coder->mutex_cond.mutex);
		}
	}
}

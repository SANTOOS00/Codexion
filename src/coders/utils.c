/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 21:07:40 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/27 12:55:00 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int		ft_get_coder_time(t_coder *coder, t_coder_status state);

bool	ft_is_simulation_finished(bool *is_sim_finished,
		pthread_mutex_t *is_sim_finished_m)
{
	bool	is_finished;

	is_finished = false;
	pthread_mutex_lock(is_sim_finished_m);
	if (*is_sim_finished == true)
		is_finished = true;
	pthread_mutex_unlock(is_sim_finished_m);
	return (is_finished);
}

bool	ft_sleep_coder(t_coder *coder, int state)
{
	struct timespec	time;

	time = ft_get_time_add_time_wait(ft_get_coder_time(coder, state));
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	pthread_cond_timedwait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex,
		&time);
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
	return (!ft_is_simulation_finished(coder->is_finished_sim,
			coder->is_finished_sim_m));
}

int	ft_get_coder_time(t_coder *coder, t_coder_status state)
{
	if (state == COMPILING)
		return (coder->config->time_to_compile);
	else if (state == DEBUGGING)
		return (coder->config->time_to_debug);
	return (coder->config->time_to_refactor);
}

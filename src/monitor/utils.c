/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:32:58 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/27 04:39:51 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
bool ft_is_finished_coder(t_coder *coder)
{
	bool is_check;

	is_check = false;
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	if (coder->compilation_count >= coder->config->number_of_compiles_required)
		is_check = true;
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
	return (is_check);
}

bool	ft_check_coder_burnout(t_coder *coder)
{
	bool	burned;

	burned = false;
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	if (coder->deadline != 0 && get_time() > coder->deadline)
		burned = true;
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
	return (burned);
}

void ft_is_burnout(bool *is_burnout_detected, pthread_mutex_t *is_burnout_detected_m)
{
	pthread_mutex_lock(is_burnout_detected_m);
	(*is_burnout_detected) = true;
	pthread_mutex_unlock(is_burnout_detected_m);
}

void ft_signal_coders_to_stop(t_coder **coders, int number_of_coders)
{
	int	i;

	i = 0;
	while (i < number_of_coders)
	{
		pthread_mutex_lock(&coders[i]->mutex_cond.mutex);
		coders[i]->has_dongle = true;
		pthread_cond_broadcast(&coders[i]->mutex_cond.cond);
		pthread_mutex_unlock(&coders[i]->mutex_cond.mutex);
		i++;
	}
}




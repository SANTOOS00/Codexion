/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_coder_burnout.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:36:24 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/22 15:52:02 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	monitor_stop_coders(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		pthread_mutex_lock(&sim->coders[i]->mutex_cond.mutex);
		sim->coders[i]->status = IS_BURNOUT;
		sim->coders[i]->has_dongle = true;
		pthread_cond_broadcast(&sim->coders[i]->mutex_cond.cond);
		pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);
		i++;
	}
}

bool	check_coder_burnout(t_coder *coder)
{
	bool	burned;

	burned = false;
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	if (coder->deadline != 0 && get_time() > coder->deadline)
		burned = true;
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
  return (burned);
}

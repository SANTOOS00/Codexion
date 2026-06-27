/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 04:23:20 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/27 04:26:14 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static bool	try_take_dongle(t_dongle *dongle);

bool	is_valid_dongl_left_right(t_coder *coder)
{
	return (try_take_dongle(coder->left_dongle)
		&& try_take_dongle(coder->right_dongle));
}

static bool	try_take_dongle(t_dongle *dongle)
{
	bool	success;

	success = false;
	pthread_mutex_lock(&dongle->mutex);
	if (dongle->is_available && get_time()
		- dongle->last_release_time >= dongle->cooldown_time)
		success = true;
	pthread_mutex_unlock(&dongle->mutex);
	return (success);
}

void	shift_queue_elements(t_queue *q)
{
	int	i;

	i = 1;
	while (i < q->size)
	{
		q->coders[i - 1] = q->coders[i];
		i++;
	}
}

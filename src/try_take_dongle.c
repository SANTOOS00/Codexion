/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_take_dongle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:12:52 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/23 05:37:00 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

bool	try_take_dongle(t_dongle *dongle)
{
	bool	success;

	pthread_mutex_lock(&dongle->mutex);
	success = false;
	if (get_time() - dongle->last_release_time >= dongle->cooldown_time
		&& dongle->is_available)
		success = true;
	pthread_mutex_unlock(&dongle->mutex);
	return (success);
}

bool	is_valid_dongl_left_right(t_coder *coder)
{
	return (try_take_dongle(coder->left_dongle)
		&& try_take_dongle(coder->right_dongle));
}

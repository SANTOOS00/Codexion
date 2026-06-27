/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_dongles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 17:11:31 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/27 04:22:28 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	return_left_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->left_dongle->mutex);
	coder->left_dongle->is_available = true;
	(coder->left_dongle->last_release_time) = get_time();
	pthread_mutex_unlock(&coder->left_dongle->mutex);
}

void	return_right_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->right_dongle->mutex);
	coder->right_dongle->is_available = true;
	(coder->right_dongle->last_release_time) = get_time();
	pthread_mutex_unlock(&coder->right_dongle->mutex);
}

void	return_dongles(t_coder *coder)
{
	return_left_dongle(coder);
	return_right_dongle(coder);
}

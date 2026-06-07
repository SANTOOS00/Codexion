/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_take_dongle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:12:52 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/07 03:23:06 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

// bool	try_take_dongle(t_dongle *dongle)
// {
// 	bool	success;

// 	pthread_mutex_lock(&dongle->m_cn_dongle.mutex);
// 	if (!(get_time() - dongle->last_release_time >= dongle->cooldown_time))
// 	{
// 		pthread_mutex_unlock(&dongle->m_cn_dongle.mutex);
// 		return (false);
// 	}
// 	success = dongle->is_available;
// 	pthread_mutex_unlock(&dongle->m_cn_dongle.mutex);
// 	return (success);
// }

bool try_take_dongle(t_dongle *dongle)
{
	bool	success;

	pthread_mutex_lock(&dongle->m_cn_dongle.mutex);
	success = false;
	if (get_time() - dongle->last_release_time >= dongle->cooldown_time
		&& dongle->is_available)
	{
		success = true;
	}
	pthread_mutex_unlock(&dongle->m_cn_dongle.mutex);
	return (success);
}
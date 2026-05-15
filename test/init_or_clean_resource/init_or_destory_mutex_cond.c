/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_or_destory_mutex_cond.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 04:06:08 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/13 16:32:00 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

bool init_mutex_cond(t_mutex_cond *mutex_cond)
{
	if (pthread_mutex_init(&mutex_cond->mutex, NULL) != 0)
		return (false);
	if (pthread_cond_init(&mutex_cond->cond, NULL) != 0)
	{
		pthread_mutex_destroy(&mutex_cond->mutex);
		return (false);
	}
	return (true);
}

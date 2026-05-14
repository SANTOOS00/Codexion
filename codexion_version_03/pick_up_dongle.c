/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_up_dongle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 17:11:45 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/14 15:25:41 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void pick_up_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->left_dongle->m_cn_dongle.mutex);
	(coder->left_dongle->is_available) = false;
	printf("%lld %d has taken a dongle\n",get_time_start_end(coder->sim) ,coder->id);
	pthread_mutex_unlock(&coder->left_dongle->m_cn_dongle.mutex);
	pthread_mutex_lock(&coder->right_dongle->m_cn_dongle.mutex);
	(coder->right_dongle->is_available) = false;
	printf("%lld %d has taken a dongle\n",get_time_start_end(coder->sim) ,coder->id);
	pthread_mutex_unlock(&coder->right_dongle->m_cn_dongle.mutex);
}
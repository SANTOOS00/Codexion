/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_up_dongle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 17:11:45 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/12 15:47:51 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
void pick_up_left_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->left_dongle->m_cn_dongle.mutex);
	(coder->left_dongle->is_available) = false;
	printf("0 %d has taken a dongle\n", coder->id);
	pthread_mutex_unlock(&coder->left_dongle->m_cn_dongle.mutex);
}

void pick_up_right_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->right_dongle->m_cn_dongle.mutex);
	(coder->right_dongle->is_available) = false;
	printf("0 %d has taken a dongle\n", coder->id);
	pthread_mutex_unlock(&coder->right_dongle->m_cn_dongle.mutex);
}


void pick_up_dongle(t_coder *coder)
{
	pick_up_left_dongle(coder);	
	pick_up_right_dongle(coder);
}
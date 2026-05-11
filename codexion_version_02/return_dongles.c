/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_dongles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 17:11:31 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/11 12:02:34 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void return_left_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->left_dongle->m_cn_dongle.mutex);
	(coder->left_dongle->is_available) = true;
	pthread_mutex_unlock(&coder->left_dongle->m_cn_dongle.mutex);
}

void return_right_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->right_dongle->m_cn_dongle.mutex);
	(coder->right_dongle->is_available) = true;
	pthread_mutex_unlock(&coder->right_dongle->m_cn_dongle.mutex);
}


void return_dongles(t_coder *coder)
{
	usleep(coder->left_dongle->cooldown_time * 1000);
	pthread_mutex_lock(&coder->queue_fifo->mutex_queue_fifo);
	return_left_dongle(coder);
	return_right_dongle(coder);
	pthread_mutex_unlock(&coder->queue_fifo->mutex_queue_fifo);
	// update_queue(coder->queue, *(coder->index_coder_left_queue));
	// update_queue(coder->queue, *(coder->index_coder_right_queue));
}
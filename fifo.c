/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:47:51 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/27 18:44:54 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
void ft_fifo(t_queue **queue, t_config config)
{
	sleep(2);
	pthread_mutex_lock(&queue[10]->coder->mutex);
    queue[10]->coder->check_wait = false;
	pthread_mutex_unlock(&queue[10]->coder->mutex);
	pthread_cond_broadcast(&queue[10]->coder->cond);
	return ;
}


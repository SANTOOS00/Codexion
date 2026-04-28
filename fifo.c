/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:47:51 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/28 12:01:25 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
void ft_fifo(t_queue **queue, t_config config)
{
	// sleep(2);
	pthread_mutex_lock(&queue[1]->coder->mutex);
    queue[1]->coder->check_wait = false;
	pthread_mutex_unlock(&queue[1]->coder->mutex);
	pthread_cond_broadcast(&queue[1]->coder->cond);
	return ;
}


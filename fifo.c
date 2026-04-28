/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:47:51 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/28 16:13:17 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
void ft_fifo(t_queue **queue, t_config config)
{
	int i;

	i = 0;
	while(queue[i])
	{
        pthread_mutex_lock(&queue[i]->coder->mutex);
		// pop_queue(queue[i]);
        queue[i]->coder->check_wait = false;
        pthread_mutex_unlock(&queue[i]->coder->mutex);
        pthread_cond_broadcast(&queue[i++]->coder->cond);
	}
	return ;
}


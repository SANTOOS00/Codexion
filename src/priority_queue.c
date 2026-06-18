/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 17:20:51 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/18 08:21:58 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	push_priority_queue(t_coder *coder)
{
	t_queue	*queue;

	queue = coder->queue;
	queue->coders[queue->size] = coder;
	if (coder->config->scheduler == EDF)
		heapify_up(queue, queue->size);
	queue->size++;
}

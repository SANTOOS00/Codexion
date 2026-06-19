/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 02:40:27 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/19 02:40:29 by moerrais         ###   ########.fr       */
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

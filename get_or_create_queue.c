/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_or_create_queue.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:12:28 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/25 12:44:21 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_queue *get_or_create_queue(int number_of_coders)
{
	static t_queue *queue;
	
	if (queue == NULL)
	{
		queue = malloc(sizeof(t_queue));
		if (!queue)
			return (NULL);
		queue->coder = malloc(sizeof(t_coder) * number_of_coders);
		if (queue->coder)
			return	NULL;
	}
	return queue;
}
-
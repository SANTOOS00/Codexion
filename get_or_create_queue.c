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

t_queue **get_or_create_queue(int number_of_coders)
{
	static t_queue **heap;
	
	if (heap == NULL)
	{
		heap = malloc(sizeof(t_queue **) * number_of_coders);
		if (!heap)
			return (NULL);
		// memset(heap, 0, sizeof(t_queue) * number_of_coders);
	}
	return heap;
}

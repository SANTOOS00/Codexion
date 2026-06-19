/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_pop_fifo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 02:40:19 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/19 02:40:21 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	shift_queue_elements(t_queue *q)
{
	int	i;

	i = 1;
	while (i < q->size)
	{
		q->coders[i - 1] = q->coders[i];
		i++;
	}
}

t_coder	*pop_queue_fifo(t_queue *q)
{
	t_coder	*coder;

	coder = NULL;
	if (q->capacity == 1 || q->size == 0)
		return (NULL);
	coder = q->coders[0];
	if (!is_valid_dongl_left_right(q->coders[0]))
		return (NULL);
	shift_queue_elements(q);
	q->size--;
	return (coder);
}

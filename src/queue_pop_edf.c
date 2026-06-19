/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_pop_edf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 02:40:11 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/19 02:40:13 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

t_coder	*pop_queue_edf(t_queue *q)
{
	t_coder		*coder;
	int			i;

	i = 0;
	coder = NULL;
	if (q->size == 0)
		return (NULL);
	if (is_valid_dongl_left_right(q->coders[0]))
	{
		coder = q->coders[0];
		q->coders[0] = q->coders[q->size - 1];
		heapify_down(q, 0);
		q->size--;
	}
	return (coder);
}

void	shift_queue_elements_edf(t_queue *queue, int index_shift)
{
	int	i;

	i = 0;
	while (index_shift > 0)
	{
		queue->coders[index_shift] = queue->coders[index_shift - 1];
		index_shift--;
	}
}

void	move_first_valid_coder_to_front(t_queue *q, int parent)
{
	int		index;
	t_coder	*coder;

	index = 0;
	while (index < q->size)
	{
		if (is_valid_dongl_left_right(q->coders[index]) && index != 0)
		{
			coder = q->coders[index];
			shift_queue_elements_edf(q, index);
			q->coders[0] = coder;
			return ;
		}
		index++;
	}
	return ;
}

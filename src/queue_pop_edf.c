/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_pop_edf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 02:40:11 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/20 17:47:14 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

t_coder	*pop_queue_edf(t_queue *q)
{
	t_coder		*coder;

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
	while (index_shift > 0)
	{
		queue->coders[index_shift] = queue->coders[index_shift - 1];
		index_shift--;
	}
}


int test_name(t_coder *coder_1, bool ret, int index)
{
	static int val_deadline;
	static int i;

	i = 0;
	val_deadline = INT_MAX;
	if (val_deadline > coder_1->deadline)
	{
		val_deadline = coder_1->deadline;
		i = index;
	}	
	if (ret)
		return (i);
	return (0);
}

void	move_first_valid_coder_to_front(t_queue *q)
{
	int		best;
	int		i;
	t_coder	*coder;

	best = -1;
	i = 0;
	while (i < q->size)
	{
		if (is_valid_dongl_left_right(q->coders[i]))
		{
			if (best == -1
				|| q->coders[i]->deadline < q->coders[best]->deadline)
				best = i;
		}
		i++;
	}
	if (best == -1)
		return ;
	coder = q->coders[best];
	shift_queue_elements_edf(q, best);
	q->coders[0] = coder;
}


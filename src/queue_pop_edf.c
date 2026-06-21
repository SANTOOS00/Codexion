/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_pop_edf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 02:40:11 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/21 23:02:28 by moerrais         ###   ########.fr       */
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

void	move_first_valid_coder_to_front(t_queue *q)
{
	int		parent;
	int		child_left;
	int		child_right;
	int		tmp;

	parent = 0;
	tmp = 0;
	if (q->size < 3 
		|| is_valid_dongl_left_right(q->coders[parent]))
		return ;
	child_left = child_left_index(parent);
	child_right = child_right_index(parent);
	if (is_same_comp(q->coders[child_right], q->coders[parent])
		&& is_valid_dongl_left_right(q->coders[child_right]))
		tmp = child_right;
	if (is_same_comp(q->coders[child_left], q->coders[parent])
		&& is_valid_dongl_left_right(q->coders[child_left]))
		tmp = child_left;
	if (tmp == parent)
		return ;
	ft_swap(&q->coders[tmp], &q->coders[parent]);
	return ;
}

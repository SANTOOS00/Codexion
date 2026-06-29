/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heapify_up_or_down.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 14:26:27 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/27 13:08:18 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static void	ft_swap(t_coder **s1, t_coder **s2);

void	heapify_up(t_queue *q, int index)
{
	int	parent;

	parent = parent_index(index);
	if (is_greater(q->coders[index], q->coders[parent]))
	{
		ft_swap(&q->coders[index], &q->coders[parent]);
		heapify_up(q, parent);
	}
	else if (is_same_deadline(q->coders[index], q->coders[parent])
		&& q->coders[index]->id < q->coders[parent]->id)
	{
		ft_swap(&q->coders[index], &q->coders[parent]);
		heapify_up(q, parent);
	}
}

void	heapify_down(t_queue *q, int parent)
{
	int	child_left;
	int	child_right;
	int	index;

	child_left = child_left_index(parent);
	child_right = child_right_index(parent);
	index = parent;
	if (child_left < q->size && is_greater(q->coders[child_left],
			q->coders[parent]))
		index = child_left;
	if (child_right < q->size && is_greater(q->coders[child_right],
			q->coders[parent]))
		index = child_right;
	if (index != parent)
	{
		ft_swap(&q->coders[index], &q->coders[parent]);
		heapify_down(q, index);
	}
}

void	ft_swap(t_coder **s1, t_coder **s2)
{
	t_coder	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

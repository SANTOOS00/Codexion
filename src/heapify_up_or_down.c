/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heapify_up_or_down.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 14:26:27 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/13 12:48:13 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	ft_swap(t_coder **s1, t_coder **s2)
{
	t_coder	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void	heapify_up(t_queue *q, int index)
{
	int	parent;

	while (index > 0)
	{
		parent = parent_index(index);
		if (is_greater(q->coders[index], q->coders[parent]))
		{
			ft_swap(&q->coders[index], &q->coders[parent]);
			index = parent;
		}
		else if (is_same_deadline(q->coders[index], q->coders[parent])
			&& q->coders[index]->id < q->coders[parent]->id)
		{
			ft_swap(&q->coders[index], &q->coders[parent]);
			index = parent;
		}
		else
			break ;
	}
}

void	heapify_down(t_queue *q, int parent)
{
	int	cheld_left;
	int	cheld_right;
	int	index;

	while (parent < q->size)
	{
		cheld_left = cheld_left_index(parent);
		cheld_right = cheld_right_index(parent);
		index = parent;
		if (cheld_left < q->size && is_greater(q->coders[cheld_left],
				q->coders[parent]))
			index = cheld_left;
		if (cheld_right < q->size && is_greater(q->coders[cheld_right],
				q->coders[cheld_right]))
			index = cheld_right;
		if (index == parent)
			break ;
		ft_swap(&q->coders[index], &q->coders[parent]);
		parent = index;
	}
}

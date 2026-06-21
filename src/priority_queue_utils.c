/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:15:58 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/21 22:58:02 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

int	parent_index(int index)
{
	return ((index - 1) / 2);
}

int	child_left_index(int index)
{
	return ((2 * index) + 1);
}

int	child_right_index(int index)
{
	return ((2 * index) + 2);
}

bool	is_greater(t_coder *coder_1, t_coder *coder_2)
{
	return (coder_1->deadline < coder_2->deadline);
}

bool	is_same_deadline(t_coder *coder_1, t_coder *coder_2)
{
	return (coder_1->deadline == coder_2->deadline);
}

bool is_same_comp(t_coder *coder_1, t_coder *coder_2)
{
	return (coder_1->compilation_count <= coder_2->compilation_count);
}

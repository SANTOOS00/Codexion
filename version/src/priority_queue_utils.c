/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:15:58 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/07 05:28:16 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

int	parent_index(int index)
{
	return ((index - 1) / 2);
}

int	cheld_left_index(int index)
{
	return ((2 * index) + 1);
}

int	cheld_right_index(int index)
{
	return ((2 * index) + 2);
}

bool	is_greater(t_dongle_request *req1, t_dongle_request *req2)
{
	return (req1->deadline < req2->deadline);
}

bool	is_same_deadline(t_dongle_request *req1, t_dongle_request *req2)
{
	return (req1->deadline == req2->deadline);
}

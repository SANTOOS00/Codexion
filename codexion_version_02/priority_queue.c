/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 14:50:59 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/10 18:13:51 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


int index_parent(int i)
{
	return ((i - 1) / 2);
}

void ft_swap(t_dongle_request **arg1, t_dongle_request **arg2)
{
	t_dongle_request *timp;
	timp = *arg1;
	*arg1 = *arg2;
	*arg2 = timp;
}

bool is_coder_ready(t_dongle_request *request)
{
	return ((request->coder->right_dongle->is_available 
		&& request->coder->left_dongle->is_available));
}

bool has_priority(t_dongle_request *req_a, t_dongle_request *req_b)
{
	bool a_ready;
	bool b_ready;

	a_ready = is_coder_ready(req_a);
	b_ready = is_coder_ready(req_b);
	if (a_ready && !b_ready)
		return (true);
	if (!a_ready && b_ready)
		return (false);
	if (req_a->deadline < req_b->deadline)
		return (true);
	return (false);
}

void heap_up(t_queue *q, int i)
{
	
}


void heap_down(t_queue *q, int i)
{

}

t_dongle_request *pop(t_queue *q)
{
	return (NULL);
}


void push_queue(t_queue *queue, t_coder *coder)
{
	return ;
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manger_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 06:27:50 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/14 16:16:59 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	puch_stack(t_malloc **nodes, t_malloc *node)
{
	t_malloc	*head_node;
	static int	i = 0;

	if (!(*nodes))
	{
		(*nodes) = node;
		i++;
		return ;
	}
	head_node = *nodes;
	while (head_node->next)
	{
		head_node = head_node->next;
	}// radi t9ad ba9i hadi anaho puch maxi nhtha flawl ok oki ok ok ok ok ok ok ok 
	head_node->next = node;
	i++;
	printf("%d\n", i);
	return ;
}

void	pull_stack(t_malloc **nodes)
{
	void	*temp_node;

	while (*nodes)
	{
		temp_node = (*nodes)->next;
		free((*nodes)->ptr);
		if(nodes->)
		free(*nodes);
		*nodes = temp_node;
	}
}

void	*manger_malloc(size_t size_byte, t_action action)
{
	static t_malloc	*nodes;
	t_malloc		*node;

	if (action == ALLOC)
	{
		node = malloc(sizeof(t_malloc));
		if (!node)
		{
			free_node(&nodes);
			return (NULL);
		}
		node->ptr = malloc(size_byte);
		if (!node->ptr)
		{
			free_node(&nodes);
			return (NULL);
		}
		node->next = NULL;
		add_node(&nodes, node);
		return (node->ptr);
	}
	else if (action == FREE)
	{
		free_node(&nodes);
		return (0);
	}
	return (NULL);
}

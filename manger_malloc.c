/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manger_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 06:27:50 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/14 08:17:25 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	add_node(t_malloc **nodes, t_malloc *node)
{
	t_malloc	*head_node;
	static int	i = 0;

	if (!(*nodes))
	{
		printf("if  ======  \n");
		(*nodes) = node;
		i++;
		return ;
	}
	head_node = *nodes;
	while (head_node->next)
	{
		printf("while ===== \n");
		head_node = head_node->next;
	}
	head_node->next = node;
	i++;
	printf("%d\n", i);
	return ;
}

void	free_node(t_malloc **nodes)
{
	void	*temp_node;

	while (*nodes)
	{
		temp_node = (*nodes)->next;
		free((*nodes)->ptr);
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

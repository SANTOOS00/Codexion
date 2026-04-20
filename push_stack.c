/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:06:03 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/20 18:06:14 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_stack	*push_stack(void *arg)
{
	static t_stack	*head_node;
	t_stack			*new_node;

	head_node = NULL;
	if (!arg)
	    return (head_node);
	new_node = malloc(sizeof(t_stack));
	if (!new_node)
	    return (NULL);
	new_node->arry_key_coders = arg;
	new_node->next = head_node;
	head_node = new_node;
	return (head_node);
}
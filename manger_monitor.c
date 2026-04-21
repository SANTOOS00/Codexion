/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manger_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 21:29:02 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/20 22:55:30 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void *manger_monitor(void *arg)
{
	t_config *config;
	t_stack *stack;

	config = (t_config *)&arg;
	t_coder **coders = get_or_create_coders(*config);
	sleep(1);
	// stack = push_stack(NULL);
	// int i = 0;
	// while(stack->next)
	// {
	// 	stack = stack->next;
	// 	i++;
	// }
	// printf("%d\n", i);
	// coders[2]->check_wait = true;
	// pthread_cond_signal(&coders[2]->cond_coder);
	return NULL;
}
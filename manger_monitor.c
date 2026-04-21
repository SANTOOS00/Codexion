/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manger_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 21:29:02 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/21 20:58:28 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void *manger_monitor(void *arg)
{
	t_config *config;
	t_stack *stack;

	usleep(1000);
	config = (t_config *)arg;
	t_stack *nodes = push_stack(NULL);
	int i = 0;
	t_coder **coders = get_or_create_coders(*config);
	
	while (nodes && nodes->next)
	{
		i++;
		t_coder *coder = (t_coder *)nodes->arry_key_coders;
		nodes = nodes->next;
		coder->check_wait = false;
		pthread_cond_broadcast(&coder->cond_coder);
		usleep(1000);
	}

	
	printf("number in codr of stack => %d\n", i);
	return NULL;
}
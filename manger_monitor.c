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



pthread_mutex_t mute;
void *manger_monitor(void *arg)
{
	t_config *config;
	t_stack *stack;

	usleep(1000);
	usleep(1000);
	config = (t_config *)arg;
	t_stack *nodes = push_stack(NULL);
	int i = 0;
	t_coder **coders = get_or_create_coders(*config);
	t_coder *coder = (t_coder *)nodes->arry_key_coders;
	while (i < 10)
	{
		t_coder *code = (t_coder *)nodes->arry_key_coders;
		
		printf("id thread in monitor => %d\n", code->id);
		pthread_mutex_lock(&coders[code->id]->left->mutex);
		coders[code->id]->check_wait = false;
		pthread_mutex_unlock(&coders[code->id]->left->mutex);
		pthread_cond_broadcast(&coders[code->id]->cond_coder);
		nodes = nodes->next;
		usleep(10);
		i++;
	}

	
	printf("number in codr of stack => %d\n", i);
	return NULL;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manger_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 21:29:02 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/25 14:53:55 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



pthread_mutex_t mute;
void *manger_monitor(void *arg)
{
	t_queue **queue;
	// pthread_mutex_lock(&mute);
	queue = get_or_create_queue(10);
	// pthread_mutex_unlock(&mute);
	printf("%p \n", queue);
	int i = 0;
	while(queue[i] != NULL)
	{
		printf("coders id  =>%d \n", queue[i]->coder->id);
		i++;
	}
	printf("%d", i);
	return NULL;
}
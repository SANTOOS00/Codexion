/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_coder_workflow.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:50:54 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/14 15:41:57 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


void enqueue_coder_request(t_coder *coder)
{
	// if (coder->status == START && coder->id % 2 != 0)
	// 	usleep(1000);
	// push_crossing(coder);
	// pthread_mutex_lock(&coder->mutex_cond.mutex);
	// coder->has_dongle = false;
    // while (!coder->has_dongle)
	// 	pthread_cond_wait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex);
	// if(coder->status == ERROR)
	// {
	// 	pthread_mutex_unlock(&coder->mutex_cond.mutex);
	// 	return ;	
	// }
	// pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void works_coders_threads(t_coder *coder)
{
	
}
bool execute_coder_workflow(t_coder *coder)
{
	printf("is execute_coder_workflow ok\n");
	// while(1)
	// {
	// 	pthread_mutex_lock(&coder->mutex_cond.mutex);
	// 	if (coder->status == ERROR)
	// 	{
	// 		pthread_mutex_unlock(&coder->mutex_cond.mutex);
	// 		break;
	// 	}
	// 	pthread_mutex_unlock(&coder->mutex_cond.mutex);
	// 	enqueue_coder_request(coder);
	// 	execute_coding_cycle(coder);
	// }
	return (true);
}
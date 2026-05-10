/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_coder_workflow.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:50:54 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/09 19:35:14 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


void refresh_coder_request(t_queue *queue, t_coder *coder)
{
	// printf("ref \n");
	return ;
}

void enqueue_coder_request(t_coder *coder)
{
	// return_dongles(coder);	
	push_queue(coder->queue, coder);
	pthread_mutex_lock(&coder->mutex_cond.mutex);
    while (coder->has_dongle)
		pthread_cond_wait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex);
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void works_coders_threads_edf(t_coder *coder)
{
	while(coder->is_burnout  != false && coder->status != FINISHED)
	{
		enqueue_coder_request(coder);
		execute_coding_cycle(coder);
		if (coder->compilation_count == coder->config->number_of_compiles_required)
			coder->status = FINISHED;
	}
}

void run_edf_routine(t_coder *coder)
{
	works_coders_threads_edf(coder);
	return ;
}

void run_fifo_routine(t_coder *coder)
{
	return ;
}

bool execute_coder_workflow(t_coder *coder)
{
	if (coder->config->scheduler == FIFO)
		run_fifo_routine(coder);
	else if(coder->config->scheduler == EDF)
		run_edf_routine(coder);
	return (true);
}
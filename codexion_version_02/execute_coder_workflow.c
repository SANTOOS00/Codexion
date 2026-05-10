/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_coder_workflow.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:50:54 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/10 18:31:55 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


void push_queue_fifo(t_coder *coder)
{
	t_queue_fifo *q;

	pthread_mutex_lock(&coder->queue_fifo->mutex_queue_fifo);
	q = coder->queue_fifo;
	q->heap[q->size] = coder;
	q->size++;
	pthread_mutex_unlock(&coder->queue_fifo->mutex_queue_fifo);
}



void enqueue_coder_request(t_coder *coder)
{
	pthread_mutex_lock(&coder->coders_cnt_lock->mutex);
	coder->run_coders_counter++;
	pthread_cond_broadcast(&coder->coders_cnt_lock->cond);
	pthread_mutex_unlock(&coder->coders_cnt_lock->mutex);

	push_queue_fifo(coder);

	pthread_mutex_lock(&coder->mutex_cond.mutex);
    while (!coder->has_dongle)
		pthread_cond_wait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex);
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void works_coders_threads_edf(t_coder *coder)
{
	while(coder->is_burnout  != false && coder->status != FINISHED)
	{
		enqueue_coder_request(coder);
		execute_coding_cycle(coder);
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
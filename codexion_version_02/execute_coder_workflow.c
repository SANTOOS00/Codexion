/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_coder_workflow.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:50:54 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/09 18:42:21 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long long get_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000));
}

int index_parent(int i)
{
	return ((i - 1) / 2);
}

void ft_swap(t_dongle_request **arg1, t_dongle_request **arg2)
{
	t_dongle_request *timp;
	timp = *arg1;
	*arg1 = *arg2;
	*arg2 = timp;
}



bool is_greater(t_dongle_request *data_1, t_dongle_request *data_2)
{
	if ((data_1->coder->right_dongle->is_available && data_1->coder->left_dongle->is_available) 
	    && !(data_2->coder->right_dongle->is_available && data_2->coder->left_dongle->is_available))
		return (true);
	if (!(data_1->coder->right_dongle->is_available && data_1->coder->left_dongle->is_available) 
	    && (data_2->coder->right_dongle->is_available && data_2->coder->left_dongle->is_available))
		return (false);
	if (data_1->deadline < data_2->deadline)
		return (true);
	return (false);
}



void push_queue(t_queue *queue, t_coder *coder)
{
	printf("push\n");
	int i;
	pthread_mutex_lock(&queue->mutex);

	i = queue->size;
	queue->heap[i]->coder = coder;
	queue->heap[i]->deadline = coder->config->time_to_burnout + get_time();
	queue->size++;
	pthread_mutex_unlock(&queue->mutex);

	while(i > 0)
	{
		pthread_mutex_lock(&queue->mutex);
		if (is_greater(queue->heap[i], queue->heap[(i - 1) / 2]))
		{
			queue->heap[i]->index_coder = (i - 1) / 2;
			queue->heap[(i - 1) / 2]->index_coder = i;
			ft_swap(&queue->heap[i], &queue->heap[index_parent(i)]);
			i = index_parent(i);
		}
		else 
		{
			
			queue->heap[i]->index_coder = i;
			pthread_mutex_unlock(&queue->mutex);
			break;
		}
		pthread_mutex_unlock(&queue->mutex);
	}	
}

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
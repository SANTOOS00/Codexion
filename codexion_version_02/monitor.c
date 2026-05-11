/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:37:59 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/11 12:01:35 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// static bool is_coder_ready(t_coder *coder)
// {
// 	bool is_dongle_valid;

// 	is_dongle_valid = false;
// 	pthread_mutex_lock(&coder->left_dongle->m_cn_dongle.mutex);
// 	pthread_mutex_lock(&coder->right_dongle->m_cn_dongle.mutex);
// 	if ((coder->right_dongle->is_available 
// 		&& coder->left_dongle->is_available))
// 		is_dongle_valid = true;
// 	pthread_mutex_unlock(&coder->left_dongle->m_cn_dongle.mutex);
// 	pthread_mutex_unlock(&coder->right_dongle->m_cn_dongle.mutex);
// 	return (is_dongle_valid);
// }
// static bool has_priority(t_dongle_request *req_a, t_dongle_request *req_b)
// {
	// 	bool a_ready;
	// 	bool b_ready;
	
	// 	a_ready = is_coder_ready(req_a);
	// 	b_ready = is_coder_ready(req_b);
	// 	if (a_ready && !b_ready)
	// 		return (true);
	// 	if (!a_ready && b_ready)
	// 		return (false);
	// 	return (false);
	// }
static bool is_coder_ready(t_coder *coder)
{
	return ((coder->right_dongle->is_available 
		&& coder->left_dongle->is_available));
}

t_dongle_request *pop_fifo(t_queue_fifo *queue_fifo)
{
	t_dongle_request *request;
	int i;

	i = 0;
	pthread_mutex_lock(&queue_fifo->mutex_queue_fifo);
	if (queue_fifo->size > 0 && is_coder_ready(queue_fifo->heap[0]->coder))
	{
		request = queue_fifo->heap[0];
		i = 1;
		while (i < queue_fifo->size)
		{
			queue_fifo->heap[i - 1] = queue_fifo->heap[i];
			i++;
		}
		queue_fifo->size--;
		pthread_mutex_unlock(&queue_fifo->mutex_queue_fifo);		
	}
	else
	{
		request = NULL;
		pthread_mutex_unlock(&queue_fifo->mutex_queue_fifo);
	}

	return (request);
}

void monitor_fifo_mode(t_simulation *sim)
{
	t_queue_fifo *q;
	t_dongle_request *request;
	int size;

	q = sim->queue_fifo;
	while (1)
	{
		request = pop_fifo(q);
		if (request)
		{
			pick_up_dongle(request->coder);
			pthread_mutex_lock(&request->coder->mutex_cond.mutex);
			
			request->coder->has_dongle = true;
			pthread_cond_broadcast(&request->coder->mutex_cond.cond);
			pthread_mutex_unlock(&request->coder->mutex_cond.mutex);	
		}
		pthread_mutex_lock(&q->mutex_queue_fifo);
		if (q->status_queue_fifo == FINISHED)
		{
			pthread_mutex_unlock(&q->mutex_queue_fifo);
			break;
		}
		pthread_mutex_unlock(&q->mutex_queue_fifo);
	}
	return;
}



void monitor_edf_mode(t_simulation *sim)
{
	while (sim->monitor_status != FINISHED_M && sim->monitor_status != ERROR_M)
	{
		
	}
}

void run_scheduler_logic(t_simulation *sim)
{
	if (sim->config.scheduler == FIFO)
		monitor_fifo_mode(sim);
	else if(sim->config.scheduler == EDF)
		monitor_edf_mode(sim);
}

void *monitor_routine(void *arg)
{
	t_simulation *sim;

	sim = (t_simulation *)arg;
	pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
	while (sim->run_coders_counter != sim->config.number_of_coders)
		pthread_cond_wait(&sim->coders_cnt_lock.cond, &sim->coders_cnt_lock.mutex);
	pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
	run_scheduler_logic(sim);
	
	return (NULL);
}

void *join_monitor(t_simulation *sim)
{
	pthread_join(sim->thread, NULL);
	return (NULL);
}

bool run_monitor_simulation(t_simulation *sim)
{
	if(pthread_create(&sim->thread, NULL, monitor_routine, sim) != 0)
		return (false);
	return (true);
}

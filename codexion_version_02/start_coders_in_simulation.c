/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_coders_in_simulation.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:42:54 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/07 10:06:49 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



void ft_swap(t_dongle_request **arg1, t_dongle_request **arg2)
{
	t_dongle_request *timp;

	timp = *arg1;
	*arg1 = *arg2;
	*arg2 = timp;
}

long long get_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000));
}


int get_index_parent(int index)
{
	return (index - 1) / 2;
}

void push_and_time_deadline(t_queue *queue, t_coder *coder)
{
	int i;
	pthread_mutex_lock(&queue->mutex);
	i = queue->size;
	queue->heap[i]->coder = coder;
	queue->heap[i]->deadline = coder->config->time_to_burnout + get_time();
	queue->size++;
	pthread_mutex_unlock(&queue->mutex);
	while (i > 0 && queue->heap[i]->deadline < queue->heap[get_index_parent(i)]->deadline)
	{
		pthread_mutex_lock(&queue->mutex);
		ft_swap(&queue->heap[i], &queue->heap[get_index_parent(i)]);
		i = get_index_parent(i);
		pthread_mutex_unlock(&queue->mutex);
	}
}

void enqueue_coder_request(t_coder *coder)
{
    t_queue *queue;

	if (coder->status == START)
	{
		push_and_time_deadline(coder->queue, coder);
	}
	// else if (coder->status == REF)
    // 	push_and_tajdid_time(coder->queue, coder);
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    while (coder->has_dongle)
        pthread_cond_wait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex);
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}



void works_coders_threads(t_coder *coder)
{
	while(coder->is_burnout  != false && coder->status != FINISH)
	{
		enqueue_coder_request(coder);
	}
}


void *coders_routine(void *arg)
{
	t_coder *coder;
	
	coder = (t_coder *)arg;	
	pthread_mutex_lock(&coder->coders_counter_m_c->mutex);
	(*coder->run_coders_counter)++;
	pthread_cond_broadcast(&coder->coders_counter_m_c->cond);
	pthread_mutex_unlock(&coder->coders_counter_m_c->mutex);
	works_coders_threads(coder);
	return (NULL);
}



void *join_coders(t_simulation *sim)
{
	int i;
	void *ret_val;

	i = 0;
	while(i < sim->config.number_of_coders)
		pthread_join(sim->coders[i++]->thread, ret_val);
	return (ret_val);
}




bool start_coders_in_simulation(t_simulation *sim)
{
	int i;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		if (pthread_create(&sim->coders[i]->thread, NULL, coders_routine, sim->coders[i]) != 0)
			return (false);
		i++;
	}
	join_coders(sim);
	return (true);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:37:59 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/09 18:36:11 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// void update_node(t_queue *q, int index, bool new_valid)

// void heap_down(t_dongle_request **heap)
// {
	
// }


// t_coder *pop(t_queue *queue)
// {
// 	t_coder *root;
// 	pthread_mutex_lock(&queue->mutex);
// 	root = queue->heap[0]->coder;
// 	queue->heap[0]->coder = queue->heap[queue->size - 1]->coder;
// 	queue->size--;
// 	heap_Down(queue->heap, 0);
// 	pthread_mutex_UNlock(&queue->mutex);
// }


void monitor_edf_mode(t_simulation *sim)
{
	// t_coder *coder;

	// while(sim->monitor_status != ERROR_M && sim->monitor_status != FINISHED_M)
	// {
	// 	if (sim->queue->size == 0)
	// 		break;
	// 	coder = pop(sim->queue);
	// 	pick_up_dongle(coder);
		
	// 	pthread_mutex_lock(&coder->mutex_cond.mutex);
	// 	coder->has_dongle = false;
	// 	pthread_cond_broadcast(&coder->mutex_cond.cond);
	// 	pthread_mutex_unlock(&coder->mutex_cond.mutex);
	// }
	return;
}

void monitor_fifo_mode(t_simulation *sim)
{
	return;
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
	usleep(1000000);
	print_queue(sim->queue);
	printf("monitor ok\n");
	run_scheduler_logic(sim);
	return (NULL);
}

void *join_monitor(t_simulation *sim)
{
	void *arg_ret;
	pthread_join(sim->thread, arg_ret);
	return (arg_ret);
}

bool run_monitor_simulation(t_simulation *sim)
{
	if(pthread_create(&sim->thread, NULL, monitor_routine, sim) != 0)
		return (false);
	return (true);
}

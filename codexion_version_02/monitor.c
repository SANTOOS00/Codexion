/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:37:59 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/07 15:12:35 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



void monitor_edf_mode(t_simulation *sim)
{
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
	printf("monitor ok\n");
	// run_scheduler_logic(sim);
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

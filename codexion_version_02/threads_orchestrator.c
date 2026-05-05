/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_orchestrator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 22:11:10 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/06 00:11:26 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void *monitor_routine(void *arg)
{
	t_simulation *sim;

	sim = (t_simulation *)arg;
	pthread_mutex_lock(&sim->coders_counter_m_c.mutex);
	while (sim->run_coders_counter != sim->config.number_of_coders)
		pthread_cond_wait(&sim->coders_counter_m_c.cond, &sim->coders_counter_m_c.mutex);
	pthread_mutex_unlock(&sim->coders_counter_m_c.mutex);
	printf("is finich in run coders dd\n");
	int i = 0;
	while (i < sim->config.number_of_coders)	
	{
		pthread_mutex_lock(&sim->coders[i]->mutex_cond.mutex);
		sim->coders[i]->is_coder_waiting = false;
		pthread_cond_broadcast(&sim->coders[i]->mutex_cond.cond);
		pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);
		i++;
	}
	return (NULL);
}


void *coders_routine(void *arg){
	t_coder *coder;

	coder = (t_coder *)arg;
	
	pthread_mutex_lock(&coder->coders_counter_m_c->mutex);
	(*coder->run_coders_counter)++;
	pthread_cond_broadcast(&coder->coders_counter_m_c->cond);
	pthread_mutex_unlock(&coder->coders_counter_m_c->mutex);



	pthread_mutex_lock(&coder->mutex_cond.mutex);
	while (coder->is_coder_waiting)
		pthread_cond_wait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex);	
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
	return (NULL);
}


bool run_monitor_simulation(t_simulation *sim)
{
	if(pthread_create(&sim->thread, NULL, monitor_routine, sim) != 0)
		return (false);

	return (true);
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
	i = 0;
	while (i < sim->config.number_of_coders)
		pthread_join(sim->coders[i++]->thread, NULL);
	pthread_join(sim->thread, NULL);
	return (true);
}

bool start_simulation(t_simulation *sim)
{
	if (run_monitor_simulation(sim) == false)	
		return (clean_resource(sim), false);
	if (start_coders_in_simulation(sim) == false)
		return (clean_resource(sim), false);	
	return (true);
		
}
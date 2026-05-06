/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_coders_in_simulation.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:42:54 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/06 04:38:17 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool wait_coders(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	while (coder->is_coder_waiting)
		pthread_cond_wait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex);	
	pthread_mutex_unlock(&coder->mutex_cond.mutex);	
	return (true);
}

void *coders_routine(void *arg)
{
	t_coder *coder;
	
	coder = (t_coder *)arg;	
	pthread_mutex_lock(&coder->coders_counter_m_c->mutex);
	(*coder->run_coders_counter)++;
	pthread_cond_broadcast(&coder->coders_counter_m_c->cond);
	pthread_mutex_unlock(&coder->coders_counter_m_c->mutex);
	if (wait_coders(coder) == false)
		return (NULL);
	return (coder);
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
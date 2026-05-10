/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_coders_in_simulation.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:42:54 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/10 18:02:55 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void *coders_routine(void *arg)
{
	t_coder *coder;

	coder = (t_coder *)arg;	
	pthread_mutex_lock(&coder->coders_cnt_lock->mutex);
	(*coder->run_coders_counter)++;
	pthread_cond_broadcast(&coder->coders_cnt_lock->cond);
	pthread_mutex_unlock(&coder->coders_cnt_lock->mutex);
	execute_coder_workflow(coder);
	return (NULL);
}

void *join_coders(t_simulation *sim)
{
	int i;

	i = 0;
	while(i < sim->config.number_of_coders)
		pthread_join(sim->coders[i++]->thread, NULL);
	return (NULL);
}

bool start_coders_in_simulation(t_simulation *sim)
{
	int i;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		if (pthread_create(&sim->coders[i]->thread, NULL, coders_routine, sim->coders[i]) != 0)
		{
			return (false);
		}
		i++;
	}
	join_coders(sim);
	return (true);
}
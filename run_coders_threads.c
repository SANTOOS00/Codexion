/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_coders_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:55:57 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/21 20:52:54 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
pthread_mutex_t mutex_pushf;
int i = 0;
void *coder_routine(void *arg)
{
	t_coder *coder = (t_coder *)arg;
	pthread_mutex_lock(&mutex_pushf);
	i++;
	// printf("%d", i);
	push_stack((void *)coder);
	pthread_mutex_unlock(&mutex_pushf);

	pthread_mutex_lock(&coder->left->mutex);
	while(coder->check_wait)
		pthread_cond_wait(&coder->cond_coder, &coder->left->mutex);
	pthread_mutex_unlock(&coder->left->mutex);
	printf("coder id %d\n", coder->id);
	return NULL;
}

t_action	run_coders_threads(t_config config)
{
	t_coder **coders;
	pthread_t monitor;
	int i;

	coders = get_or_create_coders(config);
	i = 0;
	while(i < config.number_of_coders)
	{
		if (pthread_create(&coders[i]->thread, NULL, coder_routine, coders[i]) != 0)
    		return(free_memory(fail));
		i++;
	}
	i = 0;
	if (pthread_create(&monitor, NULL, manger_monitor, &config) != 0)
	    return (free_memory(fail));
	while(i < config.number_of_coders)
	{
		pthread_join(coders[i]->thread, NULL);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		return (free_memory(fail));
	return success;
}
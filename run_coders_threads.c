/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_coders_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:55:57 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/25 14:56:09 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


void push_queue(t_coder *coder)
{
	pthread_mutex_lock(coder->mu_monitor);
    t_queue **queue;
    int i = 0;
    queue = get_or_create_queue(20);	
    while (queue[i] != NULL)
		i++;
    if (queue[i] == NULL)
    {
		queue[i] = malloc(sizeof(t_queue));
        if (!queue[i])
		return;
        queue[i]->coder = NULL;
    }
	
    queue[i]->coder = coder;
	pthread_mutex_unlock(coder->mu_monitor);
}
void *coder_routine(void *arg)
{
	
	t_coder *coder = (t_coder *)arg;
	pthread_mutex_lock(&coder->mutex);
	push_queue(coder);
	while(coder->check_wait)
		pthread_cond_wait(&coder->cond, &coder->mutex);
	pthread_mutex_unlock(&coder->mutex);
	return NULL;
}

t_action	run_coders_threads(t_config config)
{
	t_coder **coders;
	t_monitor monitor;
	int i;

	monitor.mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(monitor.mutex, NULL);
	monitor.config = config;

	coders = get_or_create_coders(config);
	get_or_create_queue(config.number_of_coders);

	i = 0;
	while(i < config.number_of_coders)
	{
		coders[i]->mu_monitor = monitor.mutex;
		if (pthread_create(&coders[i]->thread, NULL, coder_routine, coders[i]) != 0)
    		return(free_memory(fail));
		i++;
	}
	i = 0;
	if (pthread_create(&monitor.thread, NULL, manger_monitor, &monitor) != 0)
	    return (free_memory(fail));
	if (pthread_join(monitor.thread, NULL) != 0)
		return (free_memory(fail));
	while(i < config.number_of_coders)
	{
		pthread_join(coders[i]->thread, NULL);
		i++;
	}
	return monitor.action;
}
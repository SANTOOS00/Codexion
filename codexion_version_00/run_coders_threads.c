/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_coders_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:55:57 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/28 15:26:42 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void push_queue_start(t_coder *coder)
{
	int i = 0;
	t_queue *queue = get_or_create_queue(0);
	pthread_mutex_lock(&queue->mutex);
	while(queue->coder[i])
		i++;
	queue->coder[i] = coder;
	if (i + 1 == coder->config.number_of_coders)
	{
		pthread_cond_broadcast(coder->singl_monitor);
		printf("sims");
	}
	pthread_mutex_unlock(&queue->mutex);
	return ;
}

// void ft_compile(t_coder *coder)
// {
// 	usleep(coder->config.time_to_compile * 1000);
// 	printf("%ld %d is compiling\n", ft_gettime_ms(&coder->time_coder), coder->id);
// }
// void ft_debug(t_coder *coder)
// {
// 	usleep(coder->config.time_to_debug * 1000);
// 	printf("%ld %d is debugging\n", ft_gettime_ms(&coder->time_coder), coder->id);
	
// }
// void ft_refactor(t_coder *coder)
// {
	
// 	usleep(coder->config.time_to_refactor * 1000);
// 	printf("%ld %d is refactoring\n", ft_gettime_ms(&coder->time_coder), coder->id);
// }
 
void coder_worker(t_coder *coder)
{	
	pthread_mutex_lock(&coder->mutex_cd);
	coder->check_wait = true;
	while(coder->check_wait)
		pthread_cond_wait(&coder->cond_cd, &coder->mutex_cd);
	pthread_mutex_unlock(&coder->mutex_cd);
	// ft_compile(coder);
	// ft_debug(coder);
	// ft_refactor(coder);
	return ;
}

void *coder_block_until_scheduled(void *arg)
{	
	t_coder *coder = (t_coder *)arg;

	push_queue_start(coder);
	coder_worker(coder);
	return NULL;
}

t_action	run_coders_threads(t_config config)
{
	t_coder **coders;
	t_monitor monitor;
	int i;


	coders = get_or_create_coders(config);
	t_queue *queue = get_or_create_queue(0);
	i = 0;
	while(i < config.number_of_coders)
	{
		coders[i]->config = config;
		coders[i]->singl_monitor = queue->cond_monitor;
		if (pthread_create(&coders[i]->thread, NULL, coder_block_until_scheduled, coders[i]) != 0)
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
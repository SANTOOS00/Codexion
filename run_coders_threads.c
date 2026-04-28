/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_coders_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:55:57 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/28 13:48:38 by moerrais         ###   ########.fr       */
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

void ft_compile(t_coder *coder)
{
	usleep(coder->config.time_to_compile * 1000);
	printf("%ld\n", coder->config.time_to_compile);
	long time = ft_gettime_ms(&coder->time_coder);
	printf("time %ld coder id => %d\n", time, coder->id);
}
void ft_debug(t_coder *coder)
{
	usleep(coder->config.time_to_compile);
	printf("%ld\n", coder->time_coder.tv_sec);
	printf("time %ld coder id => %d\n", ft_gettime_ms(&coder->time_coder), coder->id);
	
}
void ft_refactor(t_coder *coder)
{
	struct timeval start;
	gettimeofday(&start, NULL);
	
	usleep(coder->config.time_to_compile);
	struct timeval end;
	gettimeofday(&end, NULL);
	long time = (((long)end.tv_sec * 1000L) + (end.tv_usec / 1000L)) - (((long)start.tv_sec * 1000L) + (start.tv_usec / 1000L));
	printf("time %ld coder id => %d\n", time, coder->id);
}

void coder_worker(t_coder *coder)
{	
	ft_compile(coder);
	ft_debug(coder);
	ft_refactor(coder);
	return ;
}

void *coder_block_until_scheduled(void *arg)
{	
	t_coder *coder = (t_coder *)arg;
	while(coder->config.number_of_compiles_required)
	{
		coder->config.number_of_compiles_required--;
		push_queue(coder);
		pthread_mutex_lock(&coder->mutex);
		coder->check_wait = true;
		while(coder->check_wait)
			pthread_cond_wait(&coder->cond, &coder->mutex);
		pthread_mutex_unlock(&coder->mutex);
		coder_worker(coder);
	}
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
	// struct timeval new = ft_gettime();
	while(i < config.number_of_coders)
	{
		coders[i]->mu_monitor = monitor.mutex;
		coders[i]->config = config;
		// coders[i]->time_coder = new;
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
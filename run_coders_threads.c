/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_coders_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:55:57 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/27 18:50:18 by moerrais         ###   ########.fr       */
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

struct timespec get_timespec()
{
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    return spec;
}

// void coder_worker(t_coder *coder)
// {
// 	struct timespec t = get_timespec();
// 	t.tv_nsec += coder->config.time_to_compile * 1000000;
//     if (t.tv_nsec >= 1000000000)
//     {
// 		t.tv_sec += t.tv_nsec / 1000000000;
//         t.tv_nsec %= 1000000000;
//     }
// 	unsigned long start = ft_gettime_ms();
// 	pthread_mutex_lock(&coder->mutex);
// 	printf("%ld || %d", ft_gettime(start), coder->id);
// 	pthread_cond_timedwait(&coder->cond, &coder->mutex, &t);
// 	pthread_mutex_unlock(&coder->mutex);
// 	return ;
// }
void coder_worker(t_coder *coder)
{
    unsigned long start = ft_gettime_ms();
    struct timespec t = get_timespec();
    pthread_mutex_lock(&coder->mutex);
    t.tv_nsec += coder->config.time_to_compile * 1000000;
    if (t.tv_nsec >= 1000000000)
    {
        t.tv_sec += t.tv_nsec / 1000000000;
        t.tv_nsec %= 1000000000;
    }
    printf("%ld || %d\n", ft_gettime(start), coder->id);
    pthread_cond_timedwait(&coder->cond, &coder->mutex, &t);
    pthread_mutex_unlock(&coder->mutex);
}

void *coder_block_until_scheduled(void *arg)
{	
	t_coder *coder = (t_coder *)arg;
	while(coder->config.number_of_compiles_required)
	{
		// printf("Ss\n");
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
	while(i < config.number_of_coders)
	{
		coders[i]->mu_monitor = monitor.mutex;
		coders[i]->config = config;
		if (pthread_create(&coders[i]->thread, NULL, coder_block_until_scheduled, coders[i]) != 0)
    		return(free_memory(fail));
		i++;
	}
	i = 0;
	if (pthread_create(&monitor.thread, NULL, manger_monitor, &monitor) != 0)
	    return (free_memory(fail));
	if (pthread_join(monitor.thread, NULL) != 0)
		return (free_memory(fail));
	// while(i < config.number_of_coders)
	// {
	// 	pthread_join(coders[i]->thread, NULL);
	// 	i++;
	// }
	return monitor.action;
}
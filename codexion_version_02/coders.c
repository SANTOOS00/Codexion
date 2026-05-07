/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 19:27:24 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/07 15:37:34 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder **alloc_coders(int coders_number)
{
	t_coder **coders;
	int i;

	i = 0;
	coders = (t_coder **)malloc(sizeof(t_coder *) * coders_number);
	if (!coders)
		return (NULL);
	while (i < coders_number)
	{
		coders[i] = (t_coder *)malloc(sizeof(t_coder));
		if (!coders[i])
			return (free_2d_array((void **)coders, i), NULL);
		i++;
	}
	return (coders);
}


bool ft_set_coders_initial_state(t_simulation *simulation)
{
	t_config config;
	t_coder *coder;
	int i;
	int j;

	i = 0;
	j = 0;
	config = simulation->config;
	while (i < config.number_of_coders)
	{
		coder = simulation->coders[i];
		coder->id = i;
		
		coder->has_dongle = true;
		
		coder->is_burnout = &simulation->is_burnout;
		coder->burnout_mutex = &simulation->burnout_mutex;
		
		coder->config = &simulation->config;
		
		coder->left_dongle = simulation->dongles[i];
		coder->right_dongle = simulation->dongles[(i + 1) % config.number_of_coders];
		
		coder->run_coders_counter = &simulation->run_coders_counter;
		coder->coders_cnt_lock = &simulation->coders_cnt_lock;
		
		coder->monitor_wait_lock = &simulation->monitor_wait_lock;
		coder->check_wait_monitor = &simulation->check_wait_monitor;
		
		coder->status = START;
		i++;
	}
	return (true);
}


void destory_mutex_cond_coders(t_coder **coders, int size)
{
	int i;

	i = 0;
	while (i < size)
		destory_mutex_cond(&coders[i++]->mutex_cond);
}

bool init_mutex_cond_coders(t_coder **coders, int size)
{
	int i;
	i = 0;
	while (i < size)
	{
		if (init_mutex_cond(&coders[i]->mutex_cond) == false)
		{
			destory_mutex_cond_coders(coders, i);
			return (false);
		}
		i++;
	}
	return (true);
}

void clean_coders(t_coder **coders, int size)
{
	destory_mutex_cond_coders(coders, size);
	free_2d_array((void **)coders, size);
}

bool init_coders(t_simulation *simulation)
{
	t_coder **coders;


	coders = alloc_coders(simulation->config.number_of_coders);
	if (!coders)
		return (false);
	if (init_mutex_cond_coders(coders, simulation->config.number_of_coders) == false)
	{
		free_2d_array((void **)coders, simulation->config.number_of_coders);
		return (false);
	}
	simulation->coders = coders;
	return (true);

}
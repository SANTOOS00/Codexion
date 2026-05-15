/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 19:27:24 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/13 16:31:23 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

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

	i = 0;
	config = simulation->config;
	while (i < config.number_of_coders)
	{
		coder = simulation->coders[i];
		coder->id = i + 1;
		coder->has_dongle = false;

		coder->is_burnout = &simulation->is_burnout;
		coder->burnout_mutex = &simulation->burnout_mutex;

		coder->compilation_count = 0;

		coder->config = &simulation->config;

		coder->left_dongle = simulation->dongles[i];
		coder->right_dongle = simulation->dongles[(i + 1) % config.number_of_coders];

		coder->run_coders_counter = &simulation->run_coders_counter;
		coder->coders_cnt_lock = &simulation->coders_cnt_lock;

		coder->status = START;
	

		coder->crossing = simulation->crossing;
		coder->sim	= simulation;
		coder->deadline = 0;
		i++;
	}
	return (true);
}


void destroy_mutex_cond_coders(t_coder **coders, int size)
{
	int i;

	i = 0;
	while (i < size)
		destroy_mutex_cond(&coders[i++]->mutex_cond);
}
	
bool init_mutex_cond_coders(t_coder **coders, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (init_mutex_cond(&coders[i]->mutex_cond) == false)
		{
			destroy_mutex_cond_coders(coders, i);
			return (false);
		}
		i++;
	}
	return (true);
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

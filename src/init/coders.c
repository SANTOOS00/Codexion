/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 22:14:14 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/18 08:36:03 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static t_coder	**alloc_coders(int coders_number);
static bool	init_mutex_cond_coders(t_coder **coders, int size);
static bool	ft_set_coders_initial_state(t_simulation *simulation);

bool	init_coders(t_simulation *simulation)
{
	t_coder	**coders;

	coders = alloc_coders(simulation->config.number_of_coders);
	if (!coders)
		return (false);
	if (init_mutex_cond_coders(coders,
			simulation->config.number_of_coders) == false)
	{
		free_2d_array((void **)coders, simulation->config.number_of_coders);
		return (false);
	}
	simulation->coders = coders;
	ft_set_coders_initial_state(simulation);
	return (true);
}

static t_coder	**alloc_coders(int coders_number)
{
	t_coder	**coders;
	int		i;

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

static bool	ft_set_coders_initial_state(t_simulation *simulation)
{
	t_coder	*coder;
	int		i;

	i = 0;
	while (i < simulation->config.number_of_coders)
	{
		coder = simulation->coders[i];
		coder->id = i + 1;
		coder->has_dongle = false;
		coder->is_waiting_coder = false;
		coder->compilation_count = 0;
		coder->config = &simulation->config;
		coder->left_dongle = simulation->dongles[i];
		coder->right_dongle = simulation->dongles[(i + 1)
			% simulation->config.number_of_coders];
		coder->run_coders_counter = &simulation->run_coders_counter;
		coder->watcher_mu_cond = &simulation->watch_mu_cond;
		coder->status = START;
		coder->queue = simulation->queue;
		coder->deadline = 0;
    coder->is_burnout_detected = &simulation->is_burnout_detected;
    coder->is_burnout_detected_m = &simulation->is_burnout_detected_m;
    coder->finished_coders_m = &simulation->finished_coders_m;
    coder->finished_coders = &simulation->finished_coders;
		i++;
	}
	return (true);
}

void	destroy_mutex_cond_coders(t_coder **coders, int size)
{
	int	i;

	i = 0;
	while (i < size)
		destroy_mutex_cond(&coders[i++]->mutex_cond);
}

static bool	init_mutex_cond_coders(t_coder **coders, int size)
{
	int	i;

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


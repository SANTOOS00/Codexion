/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 21:02:49 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/28 04:49:19 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static t_coder	**alloc_coders(int coders_number);
static bool		init_mutex_cond_coders(t_coder **coders, int size);
static void		ft_set_coders_initial_state(t_simulation *simulation);

bool	init_coders(t_simulation *simulation)
{
	t_coder	**coders;

	coders = alloc_coders(simulation->config.number_of_coders);
	if (!coders)
		return (false);
	if (init_mutex_cond_coders(coders,
			simulation->config.number_of_coders) == false)
	{
		ft_free_double_array((void **)coders,
			simulation->config.number_of_coders);
		return (false);
	}
	simulation->coders = coders;
	ft_set_coders_initial_state(simulation);
	if (simulation->config.number_of_coders == 1)
	{
		simulation->dongles[0]->is_available = false;
		simulation->coders[0]->deadline = get_time()
			+ simulation->config.time_to_burnout;
	}
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
			return (ft_free_double_array((void **)coders, i), NULL);
		i++;
	}
	return (coders);
}

static void	ft_set_coders_initial_state(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->config.number_of_coders)
	{
		init_coder_basic(simulation, i);
		init_coder_shared(simulation, i);
		i++;
	}
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

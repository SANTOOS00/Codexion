/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 19:04:20 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/28 22:25:51 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static t_dongle	**dongles_alloc(int dongles_number);
static bool		init_mutex_dongles(t_dongle **dongles, int dongles_number);
static void		init_dongles_state(t_dongle **dongles, t_config config);

bool	init_dongles(t_simulation *simulation)
{
	t_dongle	**dongles;

	dongles = dongles_alloc(simulation->config.number_of_coders);
	if (!dongles)
		return (false);
	if (!init_mutex_dongles(dongles, simulation->config.number_of_coders))
	{
		ft_free_double_array((void **)dongles,
			simulation->config.number_of_coders);
		return (false);
	}
	init_dongles_state(dongles, simulation->config);
	simulation->dongles = dongles;
	return (true);
}

void	clean_mutex_dongles(t_dongle **dongles, int size)
{
	int	i;

	i = 0;
	if (!dongles)
		return ;
	while (i < size)
	{
		pthread_mutex_destroy(&dongles[i]->mutex);
		i++;
	}
}

static bool	init_mutex_dongles(t_dongle **dongles, int dongles_number)
{
	int	i;

	i = 0;
	while (i < dongles_number)
	{
		if (pthread_mutex_init(&dongles[i]->mutex, NULL) != 0)
		{
			clean_mutex_dongles(dongles, i);
			return (false);
		}
		i++;
	}
	return (true);
}

static void	init_dongles_state(t_dongle **dongles, t_config config)
{
	int	i;

	i = 0;
	while (i < config.number_of_coders)
	{
		dongles[i]->is_available = true;
		dongles[i]->cooldown_time = config.dongle_cooldown;
		dongles[i]->last_release_time = 0;
		i++;
	}
}

static t_dongle	**dongles_alloc(int dongles_number)
{
	t_dongle	**dongles;
	int			i;

	i = 0;
	dongles = (t_dongle **)malloc(sizeof(t_dongle *) * dongles_number);
	if (!dongles)
		return (NULL);
	while (i < dongles_number)
	{
		dongles[i] = (t_dongle *)malloc(sizeof(t_dongle));
		if (!dongles[i])
		{
			ft_free_double_array((void **)dongles, i);
			return (NULL);
		}
		i++;
	}
	return (dongles);
}

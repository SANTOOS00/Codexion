/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 19:04:20 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/05 03:54:50 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"




t_dongle **dongles_alloc(int dongles_number)
{
	t_dongle **dongles;
	int i;

	i = 0;
	dongles = (t_dongle **)malloc(sizeof(t_dongle *) * dongles_number);
	if (!dongles)
		return (NULL);
	while (i < dongles_number)
	{
		dongles[i] = (t_dongle *)malloc(sizeof(t_dongle));
		if (!dongles[i])
			return (free_2d_array((void **)dongles, i), NULL);
		i++;
	}
	return (dongles);
}

void clean_mutex_dongles(t_dongle **dongles, int size)
{
	int i;

	i = 0;
	while (i <	size)
		pthread_mutex_destroy(&dongles[i++]->mutex);
}

void clean_dongles(t_dongle **dongles, int size)
{
	clean_mutex_dongles(dongles, size);
	free_2d_array((void **)dongles, size);
}

bool init_mutex_dongles(t_dongle **dongles, int dongles_number)
{
	int i;
	
	i = 0;
	while(i < dongles_number)
	{
		if (pthread_mutex_init(&dongles[i]->mutex, NULL))
		{
			clean_mutex_dongles(dongles, i);
			return (false);
		}
		i++;
	}
	return (true);
}


void init_dongles_state(t_dongle **dongles, long long cooldown_time)
{
	int i;

	i = 0;
	while (dongles[i] != NULL)
	{
		dongles[i]->is_available = true;
		dongles[i]->cooldown_time = cooldown_time;
		i++;
	}
}
bool alloc_and_init_dongles(t_simulation *simulation)
{
	t_dongle **dongles;


	dongles = dongles_alloc(simulation->config.number_of_coders);
	if (!dongles)
		return (false);
	if (init_mutex_dongles(dongles, simulation->config.number_of_coders) == false)
		return (free_2d_array((void **)dongles, simulation->config.number_of_coders), false);
	init_dongles_state(dongles, simulation->config.dongle_cooldown);
	simulation->dongles = dongles;
	return (true);
}
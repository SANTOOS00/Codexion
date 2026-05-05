/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 19:27:24 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/05 00:58:36 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder **coders_alloc(int coders_number)
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


t_action ft_set_coders_initial_state(t_simulation *simulation)
{
	int i;
	int j;
	t_config config;
	t_coder *coder;

	i = 0;
	j = 0;
	config = simulation->config;
	while (i < config.number_of_coders)
	{
		coder = simulation->coders[i];
		coder->id = i;
		coder->is_burnout = &simulation->is_burnout;
		coder->burnout_mutex = &simulation->burnout_mutex;
		coder->config = &simulation->config;
		coder->left_dongle = simulation->dongles[i];
		coder->right_dongle = simulation->dongles[(i + 1) % config.number_of_coders];
		coder->coders_counter = &simulation->coders_counter;
		coder->coders_counter_m_c = &simulation->coders_counter_m_c;
		coder->status = START;
		if (init_mutex_cond(&coder->mutex_cond) == FAIL)
		{
			while (++j < i)
				destory_mutex_cond(&coder->mutex_cond);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

t_action init_coders(t_simulation *simulation)
{
	t_coder **coders;


	coders = coders_alloc(simulation->config.number_of_coders);
	if (!coders)
		return (FAIL);
	simulation->coders = coders;
	return (SUCCESS);

}
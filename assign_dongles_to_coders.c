/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_dongles_to_coders.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:04:01 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/21 19:55:59 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_action assign_dongles_to_coders(t_config config)
{
	t_dongle	*dongles;
	t_coder		**coders;
	int			i;

	i = 0;
	coders = get_or_create_coders(config);
	if (!coders)
		return (fail);
	dongles = get_or_create_dongles(config);
	if (!dongles)
		return (free_memory(fail));
	while (i < config.number_of_coders)
	{
		coders[i]->left = &dongles[i];
		coders[i]->right = &dongles[(i + 1) % config.number_of_coders];
		coders[i]->id = i;
		pthread_mutex_init(&dongles[i].mutex, NULL);
		pthread_cond_init(&dongles[i].cond, NULL);
		coders[i]->check_wait = true;
		i++;
	}
	return success;
}
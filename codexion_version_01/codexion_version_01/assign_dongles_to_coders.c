/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_dongles_to_coders.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:04:01 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/02 02:45:27 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void assign_dongles_to_coders(int number_of_coders)
{
	t_dongle	*dongles;
	t_coder		**coders;
	int			i;

	i = 0;
	coders = initialize_coders(0);
	dongles = initialize_dongles(0);
	while (i < number_of_coders)
	{
		coders[i]->left = &dongles[i];
		coders[i]->right = &dongles[(i + 1) % number_of_coders];
		coders[i]->id = i;
		// pthread_mutex_init(&dongles[i].mutex, NULL);
		// pthread_cond_init(&dongles[i].cond, NULL);
		i++;
	}
	return ;
}
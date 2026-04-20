/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_dongles_to_coders.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:04:01 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/20 18:04:10 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
int assign_dongles_to_coders(t_config config)
{
	t_dongle	*dongles;
	t_coder		**coders;
	int			i;

	i = 0;
	dongles = get_or_create_dongles(config);
	coders = get_or_create_coders(config);
	while (i < config.number_of_coders)
	{
		coders[i]->left = &dongles[i];
		coders[i]->right = &dongles[(i + 1) % config.number_of_coders];
		coders[i]->id = i;
		printf("%p %d\n", coders[i], coders[i]->id);
		i++;
	}
	return 0;
}
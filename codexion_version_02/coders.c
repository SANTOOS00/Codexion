/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 19:27:24 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/04 19:27:27 by moerrais         ###   ########.fr       */
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

t_action init_coders(t_simulation *simulation)
{
	t_coder **coders;


	coders = coders_alloc(simulation->config.number_of_coders);
	if (!coders)
		return (fail);
	simulation->coders = coders;
	return (success);

}
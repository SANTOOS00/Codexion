/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_or_create_coders.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:02:21 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/20 18:02:34 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder	**get_or_create_coders(t_config config)
{
	static t_coder	**coders;
	int				i;
	
	i = 0;
	if (coders == NULL)
	{
		coders = malloc(sizeof(t_coder **) * config.number_of_coders);
		while (i < config.number_of_coders)
			coders[i++] = malloc(sizeof(t_coder));
		// coders[i] = NULL;
	}
	return (coders);
}
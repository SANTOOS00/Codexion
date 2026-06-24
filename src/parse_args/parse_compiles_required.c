/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_compiles_required.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 21:15:33 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/24 04:04:54 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

bool	parse_required_compiles(char **av, t_config *config)
{
	config->number_of_compiles_required = ft_atoi(av[6]);
	if (config->number_of_compiles_required <= 0)
	{
		error_out_of_range("number_of_compiles_required", av[6]);
		return (false);
	}
	return (true);
}

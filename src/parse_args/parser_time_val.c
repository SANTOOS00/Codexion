/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_time_val.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 21:15:36 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/05 17:23:07 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

bool	parse_com_deb_ref(char **av, t_config *config)
{
	config->time_to_compile = ft_atoi(av[3]);
	if (config->time_to_compile == -1)
	{
		error_out_of_range("time_to_compile", av[3]);
		return (false);
	}
	config->time_to_debug = ft_atoi(av[4]);
	if (config->time_to_debug == -1)
	{
		error_out_of_range("time_to_debug", av[4]);
		return (false);
	}
	config->time_to_refactor = ft_atoi(av[5]);
	if (config->time_to_refactor == -1)
	{
		error_out_of_range("time_to_refactor", av[5]);
		return (false);
	}
	return (true);
}

bool	parser_time_val(char **av, t_config *config)
{
	config->time_to_burnout = ft_atoi(av[2]);
	if (config->time_to_burnout == -1)
	{
		error_out_of_range("time_to_burnout", av[2]);
		return (false);
	}
	if (parse_com_deb_ref(av, config) == false)
		return (false);
	config->dongle_cooldown = ft_atoi(av[7]);
	if (config->dongle_cooldown == -1)
	{
		error_out_of_range("dongle_cooldown", av[7]);
		return (false);
	}
	return (true);
}

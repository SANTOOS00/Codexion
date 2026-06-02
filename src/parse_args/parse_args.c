/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:03:45 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/02 22:11:29 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"


bool	parse_args(int ac, char **av, t_config *config)
{
	//"./codexion [number_of_coders] [time_to_burnout] [time_to_compile] [time_to_refactor] [number_of_compiles_required] [dongle_cooldown] [scheduling_algorithm]"
	config->number_of_coders = 300;
	config->time_to_burnout = 1;
	config->time_to_compile = 10;
	config->time_to_debug = 10;
	config->time_to_refactor = 10;
	config->number_of_compiles_required = 110000;
	config->dongle_cooldown = 0;
	config->scheduler = EDF;
	return true;
}

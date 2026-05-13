/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:03:45 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/13 17:05:45 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

bool	parse_args(int ac, char **av, t_config *config)
{
	config->number_of_coders = 10;
	config->time_to_burnout = 100;
	config->time_to_compile = 100;
	config->time_to_debug = 100;
	config->time_to_refactor = 100;
	config->dongle_cooldown = 20;
	config->number_of_compiles_required = 3;
	config->scheduler = FIFO;
	return true;
}

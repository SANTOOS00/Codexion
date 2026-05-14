/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:03:45 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/14 16:09:39 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

bool	parse_args(int ac, char **av, t_config *config)
{
	config->number_of_coders = 21;
	config->time_to_burnout = 400;
	config->time_to_compile = 100;
	config->time_to_debug = 100;
	config->time_to_refactor = 100;
	config->dongle_cooldown = 10;
	config->number_of_compiles_required = 3;
	config->scheduler = FIFO;
	return true;
}

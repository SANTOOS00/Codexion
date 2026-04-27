/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:03:45 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/27 18:48:57 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_config	parse_args(int ac, char **av)
{
	t_config	config;

	config.number_of_coders = 20;
	config.time_to_compile = 20000000;
	config.time_to_debug = 200;
	config.time_to_refactor = 200;
	config.number_of_compiles_required = 10;
	config.dongle_cooldown = 20;
	config.scheduler = FIFO;
	return (config);
}

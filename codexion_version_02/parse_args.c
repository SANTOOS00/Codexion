/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:03:45 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/04 18:41:14 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	parse_args(int ac, char **av, t_config *config)
{
	config->number_of_coders = 20;
	config->time_to_compile = 20;
	config->time_to_debug = 20;
	config->time_to_refactor = 20;
	config->dongle_cooldown = 20;
	config->number_of_compiles_required = 2;
	config->scheduler = FIFO;
	return true;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:19:23 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/04 21:15:29 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

bool	parse_scheduler_type(char **av, t_config *config)
{
	if (!(strcmp("fifo", av[8])))
	{
		config->scheduler = FIFO;
		return (true);
	}
	if (!(strcmp("edf", av[8])))
	{
		config->scheduler = EDF;
		return (true);
	}
	fprintf(stderr, "Error: invalid scheduler '%s' (expected fifo or edf)\n",
		av[8]);
	return (false);
}

bool	parse_args(int ac, char **av, t_simulation *sim)
{
	t_config config;

	if (ac != 9)
	{
		fprintf(stderr,
				"Usage: ./codexion [number_of_coders] "
				"[time_to_burnout] [time_to_compile] "
				"[time_to_debug] [time_to_refactor] "
				"[number_of_compiles_required] [dongle_cooldown] "
				"[scheduler: fifo|edf]\n");
		return (false);
	}
	if (validate_numeric_arguments(av) == false)
		return (false);
	if (string_to_int(av, &config) == false)
		return (false);
	if (parse_scheduler_type(av, &config) == false)
		return (false);
	sim->config = config;
	return (true);
}
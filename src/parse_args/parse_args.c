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

#include "codexion.h"


bool parse_number(char **av, t_config *config)
{
	int i;
	char srg_type[6][35] = {
		"[number_of_coders]",
		"[time_to_burnout]",
		"[time_to_compile]",
		"[time_to_refactor]",
		"[number_of_compiles_required]",
		"[dongle_cooldown]", 
	};

	fprintf(stderr, "error: %s is number interger", );

	// check_number();
	return (1);
}


t_scheduler parse_fifo_or_edf(char **av, t_config *config)
{
	return 1;
}

// bool	parse_args(int ac, char **av, t_config *config)
int	main(int ac, char **av)
{
	t_config *config;

	int val_return;

	if (ac != 9)
	{
		fprintf(stderr, "./codexion [number_of_coders] [time_to_burnout] "
		"[time_to_compile] [time_to_refactor] "
		"[number_of_compiles_required] "
		"[dongle_cooldown] [scheduling_algorithm]\n");
		return (false);
	}

	if (parse_number(av, config) == false)
	{
		return (false);
	}
	if (parse_fifo_or_edf(av, config) == false)
	{
		fprintf(stderr, "error: [scheduling_algorithm] is string (fifo or edf)");
		return (false);
	}
	return true;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_numeric_arguments.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:14:55 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/03 16:58:53 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

bool	is_valid_integer(char *str_number)
{
	int	i;

	i = 0;
	while (str_number[i])
	{
		if (str_number[i] == '+' || str_number[i] == '-')
			i++;
		if (!(str_number[i] >= '0' && str_number[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

bool	validate_numeric_arguments(char **av)
{
	int	i;

	char arg_type[7][35] = {
		"number_of_coders",
		"time_to_burnout",
		"time_to_compile",
		"time_to_debug",
		"time_to_refactor",
		"number_of_compiles_required",
		"dongle_cooldown",
	};
	i = 1;
	while (i < 8)
	{
		if (is_valid_integer(av[i]) == false)
		{
			fprintf(stderr, "error: '%s' ('%s') is not a valid integer",
				arg_type[i - 1], av[i]);
			return (false);
		}
		i++;
	}
	return (true);
}

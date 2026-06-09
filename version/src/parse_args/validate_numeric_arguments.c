/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_numeric_arguments.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:14:55 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/05 16:07:45 by moerrais         ###   ########.fr       */
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
	char	arg_type[7][35];
	int		i;

	strcpy(arg_type[0], "number_of_coders");
	strcpy(arg_type[1], "time_to_burnout");
	strcpy(arg_type[2], "time_to_compile");
	strcpy(arg_type[3], "time_to_debug");
	strcpy(arg_type[4], "time_to_refactor");
	strcpy(arg_type[5], "number_of_compiles_required");
	strcpy(arg_type[6], "dongle_cooldown");
	i = 1;
	while (i < 8)
	{
		if (is_valid_integer(av[i]) == false)
		{
			fprintf(stderr, "error: '%s' ('%s') is not a valid integer\n",
				arg_type[i - 1], av[i]);
			return (false);
		}
		i++;
	}
	return (true);
}

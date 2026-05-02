/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 02:45:44 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/24 08:31:44 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



t_action	manger_threads(t_config config)
{
	if (assign_dongles_to_coders(config) == fail)
	    return (fail);
	if (run_coders_threads(config) == fail)
	    return (fail);
	return (success);
}

int	main(int ac, char **av)
{
	t_config	config;

	config = parse_args(ac, av);
	if (manger_threads(config) == fail)
		return (1);
	return (0);
}
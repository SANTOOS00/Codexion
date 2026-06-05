/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:31:06 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/05 18:02:20 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	if (ft_init_simulation(argc, argv, &simulation) == false)
		return (1);
	if (start_simulation(&simulation) == false)
	{
		clean_resource(&simulation);
		return (1);
	}
	join_threads(&simulation);
	clean_resource(&simulation);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:31:06 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/07 03:10:54 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int main(int argc, char **argv)
{
	t_simulation simulation;

	if (ft_init_simulation(argc, argv, &simulation) == false)
		return (1);
	if (start_simulation(&simulation) == false)
		return (1);
	join_monitor(&simulation);
	clean_resource(&simulation);
	return (0);
}
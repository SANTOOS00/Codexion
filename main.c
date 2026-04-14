/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:48:10 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/14 12:13:32 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



int	main(int argc, char **argv)
{
	t_config		config;
	t_threads_id	id_threads;

	parse_args(argc, argv, &config);
	create_in_threads(config, &id_threads);
}

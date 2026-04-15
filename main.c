/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:21:47 by username          #+#    #+#             */
/*   Updated: 2026/04/15 22:00:44 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int ac, char **argv)
{
	t_config	config;

	if (parse_args(ac, argv, &config))
		return (NULL);
	manger_threads(config);
}

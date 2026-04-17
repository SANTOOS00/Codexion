/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:21:47 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/16 22:14:56 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int main(int ac, char **argv)
{
	t_config config;
	if(parse_args(ac, argv, &config))
		return (1);
	if(manger_threads(config) == FREE_1)
		return (1);
	return (0);
}
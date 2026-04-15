/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:21:47 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/15 17:43:08 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int main(int ac, char **argv)
{
	t_config config;
	if(parse_args(ac, argv, &config))
		return NULL;
	manger_threads(config);
		
	
}
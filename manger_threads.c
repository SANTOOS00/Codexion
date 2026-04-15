/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manger_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:40:21 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/15 17:54:27 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int manger_threads(t_config config)
{
	int i;

	i = 0;
	while(config.number_of_coders > i)
	{
		if (create_thread())
	}
}
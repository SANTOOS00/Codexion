/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_or_create_dongles.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:01:07 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/20 18:01:23 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_dongle	*get_or_create_dongles(t_config config)
{
	static t_dongle	*dongle;

	if (dongle == NULL)
		dongle = malloc(sizeof(t_dongle) * config.number_of_coders);
	return (dongle);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manger_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:44:29 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/28 13:34:37 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

unsigned long ft_gettime_ms(struct timeval *start)
{
	struct timeval end;

	gettimeofday(&end, NULL);
	return (((long)end.tv_sec * 1000L) + (end.tv_usec / 1000L))
     - (((long)start->tv_sec * 1000L) + (start->tv_usec / 1000L));
}

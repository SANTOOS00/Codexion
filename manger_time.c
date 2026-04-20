/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manger_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:13:18 by username          #+#    #+#             */
/*   Updated: 2026/04/20 15:13:21 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

unsigned long	ft_gettime_ms(void)
{
	struct timeval	new;

	gettimeofday(&new, NULL);
	return ((new.tv_sec * 1000) + (new.tv_usec / 1000));
}

unsigned long	ft_gettime(unsigned long time_create_coder)
{
	return (ft_gettime_ms() - time_create_coder);
}

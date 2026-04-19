/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 10:32:05 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/19 10:32:29 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

unsigned long ft_gettime_ms(void)
{
    struct timeval new;
    gettimeofday(&new, NULL);
    return ((new.tv_sec * 1000) + (new.tv_usec / 1000));
}

unsigned long ft_gettime(unsigned long time_create_coder)
{
    return (ft_gettime_ms() - time_create_coder);
}
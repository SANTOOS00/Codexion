/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 21:15:23 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/05 16:00:53 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

long	ft_atoi(char *string_number)
{
	long	res;
	int		i;

	i = 0;
	res = 0;
	if (string_number[i] == '-')
		return (-1);
	if (string_number[i] == '+')
		i++;
	while (string_number[i] != '\0')
	{
		if (res > (INT_MAX - (string_number[i] - '0')) / 10)
			return (-1);
		res = 10 * res + (string_number[i] - '0');
		i++;
	}
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 23:20:35 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/04 15:39:33 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
static void error()
{
	write(2, "error: overflow", 12);
	exit(1);
}


int ft_atoi_int(char *num_str)
{
	int sing = 1;
	int i = 0;
	int res = 0;
	if (num_str[i] == '-' || num_str[i] == '+')
	{
		if (num_str[i] == '-')
			sing *= -1;
		i++;
	}
	while(num_str[i])
	{
		if (sing == 1 && res > (INT_MAX - (num_str[i] - '0')) / 10)
		{
			printf("ss");
			error();
		}
		else if (sing == -1 && res > ((INT_MIN) - (num_str[i] - '0') * -1) / 10)
		{
			printf("ss");
			error();
		}
		res = res * 10 + (num_str[i] - '0');
		i++;
	}
	return (res * sing);
}
// int main()
// {
// 	printf("number ==> %d", ft_atoi_int("12"));
// }
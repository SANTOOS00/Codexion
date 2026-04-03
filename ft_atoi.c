/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 19:56:14 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/03 20:12:17 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_atio(char *num_str)
{
	int i;
	int sing;

	sing = 1;
	i = 0;
	if (num_str  )
	if (num_str[i] == '-' || num_str[i] == '+')
	{
		if (num_str[i] == '-')
			sing = sing * -1
		i++;
	}
	else if(num_str[i])
}







int main()
{
	printf("number = %d", ft_atio("123"))
}
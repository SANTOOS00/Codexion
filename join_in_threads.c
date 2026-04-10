/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_in_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 22:38:22 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/10 23:05:40 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


void *join_in_theads(size_t number_of_codres, t_threads_id *id_ths)
{
	int i;

	i = 0;
	while(number_of_codres > i)
	{
		if(pthread_join(id_ths[i++], NULL))
			printf("is ful in thread for join number of coders %d", i);
		i++;
	}
	return ;
}
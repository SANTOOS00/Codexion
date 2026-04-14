/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_in_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 22:38:22 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/14 08:31:19 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


void *join_in_threads(size_t number_of_coders, pthread_t *threads)
{
	int i;
	void *res;
	i = 0;
	while(number_of_coders > (size_t)i)
	{
		if(pthread_join(threads[i], &res) != 0)
			printf("is ful in thread for join number of coders %d\n", i);
		i++;
	}
	return NULL;
}
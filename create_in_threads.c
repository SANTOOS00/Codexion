/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_in_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 22:25:04 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/10 23:05:34 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void *test()
{
	printf("ss")
}

void *create_in_threads(size_t number_of_coders, t_threads_id *is_threads)
{
	is_ths->thread_id = (t_threads_id)malloc(sizeof(is_threads) * number_of_codres);
	if (is_ths->thread_id)
	{
		return NULL; 
		// 5asni xi tari9a kifax n3la servec in create storj in memory
		
	}
	int i;

	i = 0;
	while(number_of_coders > i)
	{
		if(pthread_create(&is_ths->thread_id[i], NULL, &test, NULL) != 0)
			printf("error in create thread in number %d", i);
		i++;
	}
	return;
}
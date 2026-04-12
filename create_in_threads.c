/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_in_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 22:25:04 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/12 14:39:45 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
pthread_mutex_t mutex;
int i = 0;
void *test()
{
	pthread_mutex_lock(&mutex);
	i++;
	printf("task is thread  %d\n", mutex.__data.__lock);
	pthread_mutex_unlock(&mutex);
	if (i == 2)
	{
		// printf("ss\n");
		return NULL;
	}
	return (void *)1;
}
void *create_in_threads(size_t number_of_coders, t_threads_id *id_ths)
{
	id_ths->thread_id = malloc(sizeof(pthread_t) * number_of_coders);
	if (!id_ths->thread_id)
	{
		return NULL;
		// 5asni xi tari9a kifax n3la servec in create storj in memory
	}
	int i;

	i = 0;
	while(number_of_coders > (size_t)i)
	{
		if(pthread_create(&id_ths->thread_id[i], NULL, &test, NULL) != 0)
			printf("error in create thread in number %d", i);
		i++;
	}
    join_in_threads(number_of_coders, id_ths->thread_id);
	free(id_ths->thread_id);
	return NULL;
}




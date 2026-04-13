/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_in_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 22:25:04 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/13 20:13:50 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
// pthread_mutex_t mutex;
	
// int i = 0;
// void *compile(size_t time_of_comple)
// {
// 	sleep(time_of_comple);
// 	debug(time_of_debug);
// 	return NULL;
// }
// void *debug(size_t time_of_debug)
// {
// 	sleep(time_of_);
// 	refactor(time_of_refactor)
// 	return NULL;
// }
// void *refactor(size_t time_of_refactor)
// {
// 	sleep(time_of_comple);
// 	return NULL;
// }
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




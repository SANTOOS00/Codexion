/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   create_in_threads.c                               :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/04/10 22:25:04 by username         #+#    #+#              */
/*   Updated: 2026/04/14 07:30:03 by username        ###   ########.fr        */
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

void	*test(void *arg)
{
	int	*x;

	x = (int *) arg;
	printf("%d\n", *x);
	return (NULL);
}

void	*create_in_threads(size_t number_of_coders, t_threads_id *id_ths)
{
	int		i;
	size_t	size_byte = (size_t) sizeof(pthread_t) *number_of_coders;

	id_ths->thread_id = (pthread_t *) manger_malloc(size_byte, ALLOC);
	if (!id_ths->thread_id)
	{
		return (NULL);
	}
	i = 0;
	while (number_of_coders > (size_t) i)
	{
		if (pthread_create(&id_ths->thread_id[i], NULL, &test, NULL) != 0)
			printf("error in create thread in number %d", i);
		i++;
	}
	join_in_threads(number_of_coders, id_ths->thread_id);
	free(id_ths->thread_id);
	return (NULL);
}

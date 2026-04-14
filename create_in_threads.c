/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_in_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 22:25:04 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/14 12:17:04 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
// pthread_mutex_t mutex;

void *compile(size_t time_of_comple)
{
	return NULL;
}
void *debug(size_t time_of_debug)
{
	return NULL;
}
void *refactor(size_t time_of_refactor)
{
	return NULL;
}

void *coders_alternatively(t_config config)
{
	while (1)
	{
		compile(config.time_of_comple);
		compile(config.time_of_debug);
		compile(config.time_of_refactor);
	}
}
void	*create_in_threads(t_config config, t_threads_id *id_ths)
{
	int		i;
	size_t	size_byte = (size_t) sizeof(pthread_t) *number_of_coders;

	id_ths->thread_id = (pthread_t *) manger_malloc(size_byte, ALLOC);
	if (!id_ths->thread_id)
	{
		return (NULL);
	}
	i = 0;
	while (config.number_of_coders > (size_t) i)
	{
		if (pthread_create(&id_ths->thread_id[i], NULL, &coders_alternatively, &config) != 0)
			printf("error in create thread in number %d", i);
		i++;
	}
	join_in_threads(config.number_of_coders, id_ths->thread_id);
	free(id_ths->thread_id);
	return (NULL);
}

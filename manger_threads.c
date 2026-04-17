/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manger_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:40:21 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/17 00:31:01 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"




int i = 0;
void *test(void *args)
{
	t_coder *coder;
	coder = (t_coder *)args;
	pthread_mutex_lock(&coder->mutex);
	i++;
	
	printf("id coder => %d\n", coder->id);
	pthread_mutex_unlock(&coder->mutex);
	return NULL;
}

t_action create_threads(t_config config)
{
	t_manager_coder *manager;
	t_coder *coder; 
	int i;
	
	i = 0;
	manager = get_or_create_manger_coders();
	pthread_mutex_init(&manager->mutex, NULL);
	while(config.number_of_coders > i)
	{
		coder = &manager->coders[i];
		coder->mutex = &manager->mutex;
		coder->cond = &manager->cond;
		coder->id = i;
		if(pthread_create(&coder->coder, NULL, test, coder) != 0)
			return (destroy_manger_coders(FREE_1));
		i++;
	}
	pthread_mutex_destroy(coder->mutex);
	return (FREE_0);
}

t_action join_threads(t_config config)
{
	t_manager_coder *manager;
	t_coder *coder;
	int i;
	
	i = 0;
	manager = get_or_create_manger_coders();
	while(config.number_of_coders > i)
	{
		coder = &manager->coders[i];
		if(pthread_join(coder->coder, NULL) != 0)
			return (destroy_manger_coders(FREE_1));
		i++;
	}
	return (FREE_0);	
}

int manger_threads(t_config config)
{
	t_manager_coder *mag_coders;

	mag_coders = allocate_coders(config.number_of_coders);
	if (!mag_coders || !mag_coders->coders)
		return (destroy_manger_coders(FREE_1));
	if (create_threads(config) == FREE_1)
		return (destroy_manger_coders(FREE_1));
	else if (join_threads(config) == FREE_1)
		return (destroy_manger_coders(FREE_1));
	return (0);	
}
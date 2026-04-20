/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_coders_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:55:57 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/20 20:00:34 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void *coder_routine(void *arg)
{
	t_coder *coder;

	coder = (t_coder *)arg;
	printf("%p %d left %p right %p\n", coder, coder->id, coder->left, coder->right);
	return NULL;
}

t_action	run_coders_threads(t_config config)
{
	t_coder **coders;
	int i;

	coders = get_or_create_coders(config);
	i = 0;

	while(i < config.number_of_coders)
	{
		if (pthread_create(&coders[i]->thread, NULL, coder_routine, coders[i]) != 0)
    		return(free_memory(fail));
		i++;
	}
	return success;
}
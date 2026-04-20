/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 02:45:44 by username          #+#    #+#             */
/*   Updated: 2026/04/20 18:06:01 by moerrais         ###   ########.fr       */
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
void *run_coders_threads(t_config config)
{
	t_coder **coders;
	int i;
	
	coders = get_or_create_coders(config);
	i = 0;
	while(i < config.number_of_coders)
	{
		pthread_create(&coders[i]->thread, NULL, coder_routine, coders[i]);
		printf("%p %d\n", coders[i], coders[i]->id);
		i++;
	}
	i = 0;
	while(config.number_of_coders > i)
	{
		pthread_join(coders[i]->thread, NULL);
		i++;
	}
	return coders;
}




int	manger_threads(t_config config)
{
	if (assign_dongles_to_coders(config))
	    return (1);
	if (! run_coders_threads(config))
	    return (1);
	return (0);
}


int	main(int ac, char **av)
{
	t_config	config;

	config = parse_args(ac, av);
	if (manger_threads(config) == 1)
		return (1);
	return (0);
}
// int	create_coders(t_config config)
// {
// 	t_coder	*coders;
// 	int		i;

// 	i = 0;
// 	// while (config.number_of_coders > i)
// 	// {
// 	// 	pthread_create()
// 	// }
// 	return (1);
// }

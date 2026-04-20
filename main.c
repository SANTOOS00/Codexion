/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 02:45:44 by username          #+#    #+#             */
/*   Updated: 2026/04/20 17:08:13 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_stack	*push_stack(void *arg)
{
	static t_stack	*head_node;
	t_stack			*new_node;

	head_node = NULL;
	if (!arg)
	return (head_node);
	new_node = malloc(sizeof(t_stack));
	if (!new_node)
	return (NULL);
	new_node->arry_key_coders = arg;
	new_node->next = head_node;
	head_node = new_node;
	return (head_node);
}

t_dongle	*create_dongles(t_config config)
{
	static t_dongle	*dongle;

	if (dongle == NULL)
		dongle = malloc(sizeof(t_dongle) * config.number_of_coders);
	return (dongle);
}
t_coder	**create_coders(t_config config)
{
	static t_coder	**coders;
	int				i;
	
	i = 0;
	if (coders == NULL)
	{
		coders = malloc(sizeof(t_coder **) * config.number_of_coders);
		while (i < config.number_of_coders)
			coders[i++] = malloc(sizeof(t_coder));
		// coders[i] = NULL;
	}
	return (coders);
}



void *test(void *arg)
{
	t_coder *coder;

	coder = (t_coder *)arg;
	printf("%p %d\n", coder, coder->id);
	return NULL;
}
void *create_threads(t_config config)
{
	t_coder **coders;
	int i;
	
	coders = create_coders(config);
	i = 0;
	while(i < config.number_of_coders)
	{
		pthread_create(&coders[i]->thread, NULL, test, coders[i]);
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


int join_coders(t_config config)
{
	t_dongle	*dongles;
	t_coder		**coders;
	int			i;

	i = 0;
	dongles = create_dongles(config);
	coders = create_coders(config);
	while (i < config.number_of_coders)
	{
		coders[i]->left = &dongles[i];
		coders[i]->right = &dongles[(i + 1) % config.number_of_coders];
		coders[i]->id = i;
		printf("%p %d\n", coders[i], coders[i]->id);
		i++;
	}
	return 0;
}

int	manger_threads(t_config config)
{
	if (join_coders(config))
	return (1);
	if (!create_threads(config))
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

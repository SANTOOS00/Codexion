/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 21:43:59 by username          #+#    #+#             */
/*   Updated: 2026/04/15 23:00:29 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data
{
	int					id;
	long				creation_time;
	unsigned long int	coder;
	pthread_mutex_t		*mutex;
}	t_data;

typedef struct mainData
{
	t_data			*coders;
	pthread_mutex_t	print;
}	mainData;

void	compler(void *arg)
{
	t_data	*coder = (t_data *) arg;

	pthread_mutex_lock(coder->print);
	printf("coder id = %d, Number of prints %d\n", coder->id, coder->coder / 10000);
	pthread_mutex_unlock(coder->print);
}

void	*ft_routine(void *args)
{
	t_data	*coder = (t_data *) args;
	int		i = 0;

	while (i < 10)
	{
		compler(coder);
		i++;
	}
	return (NULL);
}

void	ft_create_coders(mainData * main)
{
	int	num = main->num_coders;

	if (num < 0)
		return ;
	main->coders = malloc(sizeof(t_data) * num);
	t_data	*ret = main->coders;

	for (int i = 0; i < num; i++)
	{
		ret[i].id = i + 1;
		ret[i].print = &main->print;
		ret->creation_time = 0;
		t_data
		if (pthread_create(&ret[i].coder, NULL, ft_routine, &ret[i]) != 0)
			return ;
	}
}

int	main(int c, char **v)
{
	// 3, id, print id
	if (c != 2)
	{
		return (0);
	}
	mainData main;
	main.num_coders = atoi(v[1]);
	if (pthread_mutex_init(&main.print, NULL) != 0)
		return (12);
	// allocate coders and create them
	ft_create_coders(&main);
	if (!main.coders)
		return (-1);
	// join thread and wait for cleanup
	for (int i = 0; i < main.num_coders; i++)
		if (pthread_join(main.coders[i].coder, NULL) != 0)
		return (1);
	pthread_mutex_destroy(&main.print);
	free(main.coders);
	return (0);
}
=

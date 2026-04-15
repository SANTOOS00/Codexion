/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:48:31 by username          #+#    #+#             */
/*   Updated: 2026/04/15 22:26:59 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef enum e_action
{
	ADDRESS,
	FREE
}	t_action;

typedef struct s_condif
{
	size_t		number_of_coders;
	size_t		time_to_burnout;
	size_t		time_to_compile;
	size_t		time_to_debug;
	size_t		time_to_refactor;
	size_t		number_of_compiles_required;
	size_t		dongle_cooldown;
	t_scheduler	scheduler;
}	t_config;

typedef struct s_data_thread
{
	int				id;
	long			creation_time;
	pthread_t		coder;
	pthread_mutex_t	*mutex;
	pthread_cond_t	*cond;
}	t_data_thread;

typedef struct s_manger_threads
{
	t_data_thread	*coders;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}	t_manger_threads;

int	manger_threads(t_config config);
int	parse_args(int argc, char **argv, t_config *config);

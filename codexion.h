/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   codexion.h                                        :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/04/10 21:48:31 by username         #+#    #+#              */
/*   Updated: 2026/04/14 07:10:29 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef enum e_config
{
	FIFO,
	EDF
}	t_scheduler;

typedef enum e_action
{
	ALLOC,
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

typedef struct s_malloc
{
	char			*ptr;
	struct s_malloc	*next;
}	t_malloc;

typedef struct s_threads_id
{
	pthread_t	*thread_id;
}	t_threads_id;

void	*join_in_threads(size_t number_of_numbers, pthread_t *threads);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:48:31 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/15 18:21:55 by moerrais         ###   ########.fr       */
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
	ALLOC,
	FREE
}	t_action;
// cc main1.c -pthread -fsanitize=thread -g3
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



typedef struct s_config_coders
{
	pthread_t *coders;
	unsigned long *key_coders;
	int number_coders;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
} t_condig_coders
int parse_args(int argc, char **argv, t_config *config);

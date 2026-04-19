/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:48:31 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/19 10:41:00 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>


typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;


// typedef enum e_action
// {
// 	FREE_0,
// 	FREE_1
// }	t_action;
// cc main1.c -pthread -fsanitize=thread -g3
typedef struct s_condif
{
	int		number_of_coders;
	size_t		time_to_burnout;
	size_t		time_to_compile;
	size_t		time_to_debug;
	size_t		time_to_refactor;
	size_t		number_of_compiles_required;
	size_t		dongle_cooldown;
	t_scheduler	scheduler;
}	t_config;


typedef struct s_dongle
{
	bool available;
	unsigned long dongle_cooldown;
	pthread_mutex_t mutex;
} t_dongle;

typedef struct s_coder
{
	int id;
	t_dongle *left;
	t_dongle *right;
	pthread_t th;
	long time_create;
	size_t time_compile;
} t_coder;

typedef struct s_arry_coder
{
	void *key_coders;
} t_arry_coder;

int parse_args(int argc, char **argv, t_config *config);
unsigned long ft_gettime_ms(void);
unsigned long ft_gettime(unsigned long time_create_coder);

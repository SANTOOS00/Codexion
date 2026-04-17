/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:48:31 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/17 00:32:47 by moerrais         ###   ########.fr       */
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
	FREE_0,
	FREE_1
}	t_action;
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



typedef struct s_codre
{
	int id;
	pthread_t coder;
	pthread_cond_t *cond;
	pthread_mutex_t *mutex;
} t_coder;

typedef struct s_manger_coder
{
	pthread_mutex_t *mutex;
	pthread_cond_t *cond;
	t_coder coders;
} t_manager_coder;


// typedef struct s_malloc
// {
// 	void *save;
// 	struct Node* next;
// } t_malloc;

int manger_threads(t_config config);
int parse_args(int argc, char **argv, t_config *config);
t_manager_coder *allocate_coders(int number_of_coders);
t_manager_coder *get_or_create_manger_coders();
int destroy_manger_coders(t_action action);
t_action create_threads(t_config config);
t_action join_threads(t_config config);
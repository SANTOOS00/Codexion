/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:48:31 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/28 13:28:02 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>

typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef enum e_action
{
	success,
	fail,
} t_action;

typedef struct s_condif
{
	int			number_of_coders;
	long		time_to_burnout;
	long		time_to_compile;
	long		time_to_debug;
	long		time_to_refactor;
	long		number_of_compiles_required;
	long		dongle_cooldown;
	t_scheduler	scheduler;
}	t_config;

typedef struct s_dongle
{	
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}	t_dongle;

typedef struct s_coder
{
	bool 			check_wait;
	int				id;
	pthread_t		thread;
	t_dongle		*left;
	t_dongle		*right;
	t_config		config;
	pthread_cond_t *singl_monitor;
	pthread_mutex_t mutex_cd;
	pthread_cond_t cond_cd;
}	t_coder;


typedef struct s_monitor
{
	bool cheack;
	pthread_t thread;
	t_config config;
	t_action action;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
} t_monitor;

typedef struct s_queue
{
	t_coder **coder;
	t_config config;
	pthread_mutex_t mutex;
	pthread_cond_t *cond_monitor;
} t_queue;

t_config	parse_args(int ac, char **av);
t_dongle	*get_or_create_dongles(t_config config);
t_coder		**get_or_create_coders(t_config config);
t_queue		*get_or_create_queue(int number_of_coders);
t_action	assign_dongles_to_coders(t_config config);
t_action	free_memory(t_action action);
t_action	run_coders_threads(t_config config);
void	*manger_monitor(void *arg);
void ft_fifo(t_queue **queue, t_config config);
void ft_edf(t_queue **queue, t_config config);
unsigned long	ft_gettime_ms(struct timeval *start);
// void push(struct Node * *head_ref,
//int	new_data)
// {
// 	// 1. Allocate node
// 	struct Node	*new_node =
// 	(struct Node *) malloc(sizeof(struct Node));

// 	// 2. put in the data
// 	new_node->data = new_data;

// 	// 3. Make next of new node as head
// 	new_node->next = (*head_ref);

// 	// 4. move the head to point to
// 	// the new node
// 	(*head_ref) = new_node;
// }

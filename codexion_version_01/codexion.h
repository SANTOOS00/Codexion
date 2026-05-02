/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 16:54:33 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/02 18:37:59 by moerrais         ###   ########.fr       */
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

typedef enum e_queue_state
{
    QUEUE_INCOMPLETE,
    QUEUE_COMPLETE
}   t_queue_state;

typedef enum e_action
{
	success,
	fail,
	fail_coders,
    fail_dongles,
    fail_queue,
	// exit,
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
    int				id;
	// t_action		action;
	bool			check_wait;
	pthread_t		thread;
	t_dongle		*left;
	t_dongle		*right;
	pthread_mutex_t *mutex;
	pthread_cond_t cond;
}	t_coder;



typedef struct s_queue
{
	int index_coder;
	pthread_mutex_t *mutex;
} t_queue;


// parsion
t_config	parse_args(int ac, char **av);

//assign dongle to coders
void assign_dongles_to_coders(int number_of_coders);

//free resource
void free_source(t_action action, int number_of_coders);

//initialize sources heap and return pointeur in source
t_coder		**initialize_coders(int number_of_coders);
t_dongle	*initialize_dongles(int number_of_coders);
t_queue		**initialize_queue(int number_of_coders);




void push_queue(t_coder *coder);



// is queue full
void is_queue_full(int number_of_coders);

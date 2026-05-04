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


// typedef enum e_queue_state
// {
	// }   t_queue_state;
	
	// typedef enum e_action
	// {
		// } t_action;
		
typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef enum e_coder_status {
	START,
	WAIT,
	COMP,
	DEBUG,
	REF,
	FINISH,
} t_coder_status;

typedef struct s_config
{
	int			number_of_coders;
	int			time_to_burnout;
	int			time_to_compile;
	int			time_to_debug;
	int			time_to_refactor;
	int			number_of_compiles_required;
	int			dongle_cooldown;
	t_scheduler	scheduler;
}	t_config;

typedef struct s_dongle
{
	pthread_mutex_t mutex;
	bool is_available;
	int cooldown_time;
}	t_dongle;

typedef struct s_mutex_cond {
	pthread_mutex_t mutex;
	pthread_cond_t cond;
} t_mutex_cond;

typedef struct s_coder
{
	int id;
	bool check_wait;
	bool *is_burnout;
	pthread_mutex_t *burnout_mutex;
	pthread_t thread;
	t_config *config;
	t_dongle *left_dongle;
	t_dongle *right_dongle;
	int *coders_counter;
	t_mutex_cond *coders_counter_m_c;
	t_coder_status status;
	t_mutex_cond mutex_cond;
	pthread_mutex_t *print_mutex;
}	t_coder;


typedef struct s_queue
{
	void **coders;
	int size;
	int max_size;
} t_queue;

typedef struct s_simulation {
	t_config config;
	t_coder **coders;
	t_dongle **dongles;
	int coders_counter;
	t_mutex_cond coders_counter_m_c;
	bool is_burnout;
	pthread_mutex_t burnout_mutex;
	t_queue queue;
	pthread_mutex_t print_mutex;
} t_simulation;

// init coders
bool ft_init_coders(t_simulation *simulation);
void ft_join_coders_threads(t_simulation *simulation);
bool ft_run_coders_threads(t_simulation *simulation);

// parse the args
bool	parse_args(int ac, char **av, t_config *config);
bool 	ft_init_simulation(char **argv, int argc, t_simulation *simulation);
bool 	ft_init_mutex_cond_var(t_mutex_cond *mutex_cond);
bool ft_init_simulation(char **argv, int argc, t_simulation *simulation);
void ft_destrory_mutex_cond_var(t_mutex_cond *mutex_cond);

// dongles 
bool ft_init_dongles(t_simulation *simulation);
void ft_clean_dongles(t_simulation *simulation);
void ft_free_resource(void **args, int cont);
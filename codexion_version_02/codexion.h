/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 16:54:33 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/07 03:08:01 by moerrais         ###   ########.fr       */
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

typedef struct s_queue t_queue;

// typedef enum e_queue_state
// {
	// }   t_queue_state;
	
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
	pthread_t thread;
	bool has_dongle;
	int id;
	bool *is_burnout;
	pthread_mutex_t *burnout_mutex;
	t_config *config;
	t_dongle *left_dongle;
	t_dongle *right_dongle;
	int *run_coders_counter;
	t_mutex_cond *coders_counter_m_c;
	t_coder_status status;
	t_mutex_cond mutex_cond;
	t_queue *queue;
	pthread_mutex_t *queue_mutex;
}	t_coder;


typedef struct s_dongle_request
{
	t_coder	*coder;
	long long	deadline;  //deadline = last_compile_start + time_to_burnout
}	t_dongle_request;

typedef struct s_queue
{
	t_dongle_request	**heap;
	int					size; //xhal 3ndi f heap
	int					capacity;  // hnay xhal i9dr ihz lina heap ya3ni xhal max dyalo
	pthread_mutex_t mutex;
}	t_queue;


typedef struct s_simulation {
	pthread_t thread;
	t_config config;
	t_coder **coders;
	t_dongle **dongles;
	int run_coders_counter;
	t_mutex_cond coders_counter_m_c;//
	bool is_burnout;
	pthread_mutex_t burnout_mutex;//
	t_queue *queue;
	pthread_mutex_t queue_mutex;//
} t_simulation;



// parse the args
bool	parse_args(int ac, char **av, t_config *config);


// init simulation
bool ft_init_simulation(int argc, char **argv, t_simulation *simulation);
bool init_coders(t_simulation *simulation);
bool alloc_and_init_dongles(t_simulation *simulation);

t_coder **alloc_coders(int coders_number);

void *join_monitor(t_simulation *sim);

// free 2d arry void ** and size for free
void free_2d_array(void **arr, int size);

bool init_mutex_cond(t_mutex_cond *mutex_cond);
void destory_mutex_cond(t_mutex_cond *mutex_cond);


t_queue *get_queue();

bool init_mutex_cond(t_mutex_cond *mutex_cond);


void clean_mutex_cond_simulation(t_simulation *simulation);

void clean_mutex_dongles(t_dongle **dongles, int size);
// set coder in state
bool ft_set_coders_initial_state(t_simulation *simulation);

void clean_coders(t_coder **coders, int size);
void clean_dongles(t_dongle **dongles, int size);
void clean_mutex_cond_simulation(t_simulation *simulation);
void clean_resource(t_simulation *simulation);



//manger moniter 
bool run_monitor_simulation(t_simulation *sim);


bool ft_init_queue(t_simulation *sim);


void clean_queue(t_queue *queue);

// manger in fifo or edf
bool ft_fifo_or_edf(t_simulation *sim);


// start coders in simulation 
bool start_coders_in_simulation(t_simulation *sim);


// wait coder
void wait_coder(t_coder *coder);

// run simulation 
bool start_simulation(t_simulation *sim);
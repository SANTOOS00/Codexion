/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 16:54:33 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/11 10:46:35 by moerrais         ###   ########.fr       */
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

typedef struct s_queue_fifo t_queue_fifo;

// typedef enum e_queue_state
// {
	// }   t_queue_state;
	
typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef enum e_coder_status 
{
    START,              // Initial state
    WAIT_FOR_DONGLE,    // Waiting for resource availability or cooldown
    COMPILING,          // Currently in the compilation phase
    DEBUGGING,          // Currently in the debugging phase
    REFACTORING,        // Currently in the refactoring phase
    FINISHED,           // Workflow completed successfully
    ERROR               // Generic error (e.g., thread creation failure)
} t_coder_status;


typedef enum e_monitor_status
{
	START_M,              // Initial state
	FINISHED_M,           // Workflow completed successfully
	ERROR_M           // Generic error (e.g., thread creation failure)
	
} t_monitor_enum_status;

typedef struct s_config
{
	int					number_of_coders;
	int					time_to_burnout;
	int					time_to_compile;
	int					time_to_debug;
	int					time_to_refactor;
	int					number_of_compiles_required;
	long long			dongle_cooldown;
	t_scheduler			scheduler;
}	t_config;

typedef struct s_mutex_cond {
	pthread_mutex_t 	mutex;
	pthread_cond_t 		cond;
} t_mutex_cond;

typedef struct s_dongle
{
 	t_mutex_cond		m_cn_dongle;
	bool				is_available;
	int					cooldown_time;
}	t_dongle;



typedef struct s_coder
{
	pthread_t 		thread;
	int 			id;
	bool 			has_dongle; /// kaytsna dongles min monitor i3tihom lih
	
	bool 			*is_burnout;
	pthread_mutex_t *burnout_mutex;
	
	int				compilation_count;
	int				index_in_queue;
	int				*index_coder_left_queue;
	int				*index_coder_right_queue;
	
	
	t_config 		*config;
	
	t_dongle 		*left_dongle;
	t_dongle 		*right_dongle;
	
	int 			*run_coders_counter;
	t_mutex_cond 	*coders_cnt_lock;
	
	t_coder_status 	status;
	t_mutex_cond 	mutex_cond;
	
	bool			*check_wait_monitor;  // القفل الخاص بالعداد
	t_mutex_cond	*monitor_wait_lock;
	
	
	t_queue_fifo 	*queue_fifo;
}	t_coder;

typedef struct s_queue_fifo
{
	t_coder 		**heap;
	int 			size;
	int				capacity;
	t_coder_status	status_queue_fifo;
	pthread_mutex_t mutex_queue_fifo;

} t_queue_fifo;

typedef struct s_dongle_request
{
	t_coder			*coder;
	long long		deadline;  //deadline = last_compile_start + time_to_burnout
}	t_dongle_request;

typedef struct s_queue
{
	t_dongle_request	**heap;
	
	int					size; //xhal 3ndi f heap
	
	int					capacity;  // hnay xhal i9dr ihz lina heap ya3ni xhal max dyalo
	pthread_mutex_t 	mutex_queue_priority;
}	t_queue;





typedef struct s_simulation
{
    pthread_t       			thread;
    t_config        			config;

    t_coder         			**coders;
    t_dongle        			**dongles;

	t_monitor_enum_status		monitor_status;// الجزء الخاص بالعداد والمراقبة
    int             			run_coders_counter;
    t_mutex_cond    			coders_cnt_lock; 

	bool						check_wait_monitor;  // القفل الخاص بالعداد
    t_mutex_cond				monitor_wait_lock;  // القفل الخاص بانتظار المراقبة (Wait Monitor)

	bool            			is_burnout;
    pthread_mutex_t 			burnout_mutex;

	t_queue         			*queue_priority;
	t_queue_fifo 				*queue_fifo;

} t_simulation;


// parse the args
bool	parse_args(int ac, char **av, t_config *config);




// init resource and free resource
bool 		init_mutex_cond(t_mutex_cond *mutex_cond);
bool 		ft_init_simulation(int argc, char **argv, t_simulation *simulation);
bool 		init_coders(t_simulation *simulation);
bool 		alloc_and_init_dongles(t_simulation *simulation);
bool 		init_mutex_cond(t_mutex_cond *mutex_cond);
bool		ft_init_queue_fifo(t_simulation *sim);


void 		clean_coders(t_coder **coders, int size);
void 		free_2d_array(void **arr, int size);
void 		clean_dongles(t_dongle **dongles, int size);
void 		clean_mutex_cond_simulation(t_simulation *simulation);
void 		clean_resource(t_simulation *simulation);
t_coder		**alloc_coders(int coders_number);
void		clean_queue_pro(t_queue *queue);
void		clean_queue_fifo(t_queue_fifo *queue);
void 		destory_mutex_cond(t_mutex_cond *mutex_cond);




bool has_priority(t_dongle_request *data_1, t_dongle_request *data_2);
// init simulation

void *join_monitor(t_simulation *sim);

// free 2d arry void ** and size for free

void print_data_queue(t_queue_fifo *fifo);



void clean_mutex_cond_simulation(t_simulation *simulation);

void clean_mutex_dongles(t_dongle **dongles, int size);
// set coder in state
bool ft_set_coders_initial_state(t_simulation *simulation);





void ft_swap(t_dongle_request **arg1, t_dongle_request **arg2);
t_dongle_request *pop(t_queue *queue);
void heap_down(t_queue *queue, int i);
// void update_queue(t_queue *q, int index);


//manger moniter 



bool run_monitor_simulation(t_simulation *sim);


bool ft_init_queue(t_simulation *sim);



// manger in fifo or edf
bool execute_coder_workflow(t_coder *coder);
void run_scheduler_logic(t_simulation *sim);


// start coders in simulation 
bool start_coders_in_simulation(t_simulation *sim);

void print_queue(t_queue *queue);

// wait coder
// void wait_coder(t_coder *coder);


// work in coder for mange in monitor
void execute_coding_cycle(t_coder *coder);


void push_queue(t_queue *queue, t_coder *coder);


long long get_time();

// return and 
void pick_up_dongle(t_coder *coder);
void return_dongles(t_coder *coder);



// run simulation 
bool start_simulation(t_simulation *sim);
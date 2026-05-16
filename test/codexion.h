/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 16:54:33 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/16 14:36:11 by moerrais         ###   ########.fr       */
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

typedef enum e_coder_status 
{
	START,
    COMPILING,
    DEBUGGING,
    REFACTORING,
    FINISHED,
    ERROR
} t_coder_status;


typedef enum e_monitor_status
{
	START_M,
	FINISHED_M,
	ERROR_M
	
} t_monitor_status;

typedef enum e_watch_status
{
	START_W,
	FINISHED_W,
	ERROR_W
} t_watch_status;


typedef struct s_queue_normal t_queue_normal;
typedef struct s_simulation t_simulation;

typedef struct s_config
{
	int					number_of_coders;
	long long			time_to_burnout;
	long long			time_to_compile;
	long long			time_to_debug;
	long long			time_to_refactor;
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
	long long			cooldown_time;
	long long			last_release_time;
}	t_dongle;



typedef struct s_coder
{
	pthread_t 			thread;
	int 				id;
	bool 				has_dongle;
	long long			deadline;
	bool 				*is_burnout;
	pthread_mutex_t 	*burnout_mutex;
		
	int					compilation_count;
	
		
		
	t_config 			*config;
		
	t_dongle 			*left_dongle;
	t_dongle 			*right_dongle;
		
	int 				*run_coders_counter;
	t_mutex_cond 		*coders_cnt_lock;
		
	t_coder_status 		status;
	t_mutex_cond 		mutex_cond;	
		
	t_queue_normal 	*queue_normal;	
	t_simulation		*sim;
}	t_coder;

typedef struct s_queue_normal
{
	t_coder 		**heap;

	int 			size;
	int				capacity;

	pthread_mutex_t mutex_crossing;

} t_queue_normal;

typedef struct s_dongle_request
{
	t_coder				*coder;
	long long 			deadline;
}	t_dongle_request;

typedef struct s_queue
{
	t_dongle_request	**heap;
	
	int					size;
	
	int					capacity;
	long long			time_burnout;
	pthread_mutex_t 	mutex_queue;
}	t_queue;





typedef struct s_simulation
{
    pthread_t           monitor_tid;
    pthread_t           watcher_tid;


    t_config            config; 
    long long           time_start;


    t_coder             **coders;
    t_dongle            **dongles;
    t_queue             *queue;
    t_queue_normal    *queue_normal;


    t_monitor_status    monitor_status;
    int                 run_coders_counter;
    t_mutex_cond        coders_cnt_lock;

	
    t_watch_status      watch_status;
    bool                is_watch_waiting;
    t_mutex_cond        watch_lock;
    
    bool                is_burnout;
    pthread_mutex_t     burnout_mutex;

} t_simulation;

/* ************************************************************************** */
/*                                                                            */
/*                          1. UTILITIES & TIME                               */
/*           دوال المساعدة، الوقت، ومعالجة المدخلات (Parsing)                 */
/* ************************************************************************** */

long long   get_time(void);
long long   get_time_start_end(t_simulation *sim);
bool        parse_args(int ac, char **av, t_config *config);


/* ************************************************************************** */
/*                         2. INITIALIZATION (ALLOC & INIT)                   */
/*             دوال حجز الذاكرة والتهيئة الأولية لكل الموارد                  */
/* ************************************************************************** */

bool        ft_init_simulation(int argc, char **argv, t_simulation *simulation);
bool        init_coders(t_simulation *simulation);
t_coder     **alloc_coders(int coders_number);
bool        alloc_and_init_dongles(t_simulation *simulation);
bool        ft_init_queue(t_simulation *sim);
bool		ft_init_queue_normal(t_simulation *sim);
bool        ft_set_coders_initial_state(t_simulation *simulation);
bool        init_mutex_cond(t_mutex_cond *mutex_cond);


/* ************************************************************************** */
/*                          3. CORE SIMULATION LOGIC                          */
/*            قلب المحاكاة: تشغيل الخيوط (Threads) والمنطق الأساسي             */
/* ************************************************************************** */

bool        start_simulation(t_simulation *sim);
void		coder_main_loop(t_coder *coder);
void		*coder_routine(void *arg);
void		*watcher_routine(void *arg);
void		*monitor_routine(void *arg);

// سير عمل المبرمج 
void		perform_coding(t_coder *coder);
// bool        execute_coder_workflow(t_coder *coder);
// void        execute_coding_cycle(t_coder *coder);
void        pick_up_dongle(t_coder *coder);
void        return_dongles(t_coder *coder);

// // منطق عبور التقاطع (Crossing Logic)
// void        initiate_crossing_logic(t_simulation *sim);
void        run_fifo_routine(t_simulation *sim);
void        run_edf_routine(t_simulation *sim);


/* ************************************************************************** */
/*                         4. QUEUE & SCHEDULING MANAGEMENT                   */
/*                 إدارة الطابور، الجدولة، وحالة المبرمجين                     */
/* ************************************************************************** */


void			push_normal_queue(t_coder *coder);
void 			add_queue_normal_to_queue(t_queue_normal *queue_normal, t_queue *queue, t_scheduler scheduler);
void        	push_to_priority_queue(t_queue *q, t_coder *coder, t_scheduler sch);
void 			push_normal_queue(t_coder *coder);
void			heapify_up(t_queue *q, int index);
t_coder			*pop_queue(t_queue *q, t_scheduler scheduler);

t_coder_status  get_status_coder(t_coder *coder);
// bool            get_is_burnout_monitor(t_simulation *sim);


/* ************************************************************************** */
/*                          5. THREADS JOINING & EXIT                         */
/*                   دوال انتظار انتهاء الخيوط والخروج الآمن                   */
/* ************************************************************************** */

void        join_monitor(t_simulation *sim);
void        join_watcher(t_simulation *sim);
void        join_coders(t_simulation *sim, int number_coders);
void		join_threads(t_simulation *sim);

void        exit_monitor(t_simulation *sim);
void        exit_watcher(t_simulation *sim);
void        exit_coders(t_simulation *sim, int number_coders);


/* ************************************************************************** */
/*                          6. CLEANUP & MEMORY DEALLOC                       */
/*                 تنظيف الميوتكسات وتحرير الذاكرة (Freeing)                  */
/* ************************************************************************** */

void        destroy_mutex_cond(t_mutex_cond *mutex_cond);
void        clean_mutex_cond_simulation(t_simulation *simulation);
void        clean_mutex_dongles(t_dongle **dongles, int size);
void        clean_dongles(t_dongle **dongles, int size);
void        clean_queue(t_queue *queue);
void		clean_queue_normal(t_queue_normal *queue_normal);
void        clean_coders(t_coder **coders, int size);
void        free_2d_array(void **arr, int size);
void        clean_resource(t_simulation *simulation);
void		destroy_mutex_cond_coders(t_coder **coders,int size);







/// routine threads coder and monitor and watcher

/// join  threads 


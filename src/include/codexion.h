/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 16:54:33 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/24 04:16:19 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>

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
	ERROR
}	t_coder_status;

typedef enum e_monitor_status
{
	START_M,
	FINISHED_M,
	ERROR_M
}	t_monitor_status;

typedef enum e_watch_status
{
	START_W,
	FINISHED_W,
	IS_BURNOUT_W,
	ERROR_W
}	t_watch_status;

typedef enum e_arg_type
{
	number_of_coders,
	time_to_burnout,
	time_to_compile,
	time_to_refactor,
	number_of_compiles_required,
	dongle_cooldown
}	t_arg_type;

/*
** ============== FORWARD DECLARATION ==============
*/

typedef struct s_queue			t_queue;
typedef struct s_simulation		t_simulation;

/*
** ================= CONFIG =================
*/

typedef struct s_config
{
	long			number_of_coders;
	long			time_to_burnout;
	long			time_to_compile;
	long			time_to_debug;
	long			time_to_refactor;
	long			number_of_compiles_required;
	long			dongle_cooldown;
	t_scheduler		scheduler;
}	t_config;

/*
** ================= SYNC =================
*/

typedef struct s_mutex_cond
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}	t_mutex_cond;

/*
** ================= DONGLE =================
*/

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	bool			is_available;
	long long		cooldown_time;
	long long		last_release_time;
}	t_dongle;

/*
** ================= CODER =================
*/

typedef struct s_coder
{
	pthread_t		thread;
	int				id;
	bool			is_waiting_coder;
	long long		deadline;
	bool			*is_burnout;
	pthread_mutex_t	*burnout_mutex;

	int				compilation_count;
	t_config		*config;

	long long		*time_start;

	pthread_mutex_t *mutex_print;

	t_dongle		*left_dongle;
	t_dongle		*right_dongle;

	int				*run_coders_counter;
	bool			has_dongle;
	t_mutex_cond	*watcher_mu_cond;

	t_queue			*queue;
	t_coder_status	status;
	t_mutex_cond	mutex_cond;

	t_simulation	*sim;

	bool			*is_finished_sim;
	pthread_mutex_t *is_finished_sim_m;

  	// int				*finished_coders;
 	// pthread_mutex_t *finished_coders_m;
}	t_coder;

/*
** ================= PRIORITY QUEUE =================
*/

typedef struct s_queue
{
	t_coder				**coders;
	int					size;
	int					capacity;
	pthread_mutex_t		mutex_queue;
}	t_queue;

/*
** ================= SIMULATION =================
*/

typedef struct s_simulation
{
	pthread_t			monitor_tid;
	pthread_t			watcher_tid;

	pthread_mutex_t		mutex_print;
	t_config			config;
	long long			time_start;

	t_coder				**coders;
	t_dongle			**dongles;
	t_queue				*queue;

	t_monitor_status	monitor_status;
	int					run_coders_counter;
	t_mutex_cond		monitor_mu_cond;

	t_watch_status		watch_status;
	bool				is_watch_waiting;
	t_mutex_cond		watch_mu_cond;

	int           		finished_coders;
	pthread_mutex_t		finished_coders_m;

	bool				is_finished_sim;
	pthread_mutex_t		is_finished_sim_m;
}	t_simulation;

/*
** ================= UTILITIES =================
*/

long long			get_time(void);
long long			get_time_start_end(t_coder *coder);
struct timespec		get_time_add_time_wait(long long time_wait_ms);

bool				parse_args(int ac, char **av, t_simulation *sim);
bool				is_valid_integer(char *str);
bool				validate_numeric_arguments(char **av);
bool				string_to_int(char **av, t_config *config);
bool				parser_time_val(char **av, t_config *config);
bool				parse_required_compiles(char **av, t_config *config);

long				ft_atoi(char *str);
void				error_out_of_range(const char *arg, const char *val);
// bool				is_burnout_detected(bool *is_burnout_detected, pthread_mutex_t *is_burnout_detected_m);

void				update_burnout_timer(t_coder *coder);
void				increment_coders_counter(t_coder *coder);
bool				is_valid_dongl_left_right(t_coder *coder);
void				print_coder_action(t_coder *coder, char *action);

/*
** ================= INIT =================
*/

bool				ft_init_simulation(int ac, char **av, t_simulation *sim);
void				initialize_start_time(t_simulation *sim);

bool				init_coders(t_simulation *sim);
bool				init_dongles(t_simulation *sim);
bool				ft_init_queue(t_simulation *sim);
bool				init_mutex_cond(t_mutex_cond *m);

/*
** ================= CORE / ROUTINES =================
*/

bool				start_simulation(t_simulation *sim);

void				*coder_routine(void *arg);
void				coder_main_loop(t_coder *coder);
// void				start_coder_compilation_cycle(t_coder *coder);
bool				perform_coding(t_coder *coder);

void				pick_up_dongle(t_coder *coder);
bool				try_take_dongle(t_dongle *dongle);
void				return_dongles(t_coder *coder);

void				*watcher_routine(void *arg);
// void				watcher_wake_monitor(t_simulation *sim);
// void				watcher_stop_monitor(t_simulation *sim);
bool ft_is_simulation_finished(bool *is_sim_finished, pthread_mutex_t *is_sim_finished_m);
// void				watcher_stop_coders(t_simulation *sim);

void				*monitor_routine(void *arg);

/*
** ================= SCHEDULER & QUEUE =================
*/

void				push_priority_queue(t_coder *coder);
t_coder				*pop_queue(t_simulation *sim, t_scheduler scheduler);
t_coder				*pop_queue_edf(t_queue *q);
t_coder				*pop_queue_fifo(t_queue *q);

void				heapify_up(t_queue *q, int index);
void				heapify_down(t_queue *q, int parent);
void				ft_swap(t_coder **s1, t_coder **s2);

int					parent_index(int index);
int					child_left_index(int index);
int					child_right_index(int index);

bool				is_same_deadline(t_coder *coder_1, t_coder *coder_2);
bool				is_same_comp(t_coder *coder_1, t_coder *coder_2);
bool				is_greater(t_coder *coder_1, t_coder *coder_2);
void				move_first_valid_coder_to_front(t_queue *q);

/*
** ================= STATUS & CHECKS =================
*/

t_coder_status		get_status_coder(t_coder *coder);
t_watch_status		get_watcher_status(t_simulation *sim);
t_monitor_status	get_status_monitor(t_simulation *sim);

bool				check_coder_burnout(t_coder *coder);
/*
** ================= THREADS MANAGEMENT =================
*/

void				join_threads(t_simulation *sim);
void				join_coders(t_simulation *sim, int n);
void				join_watcher(t_simulation *sim);
void				join_monitor(t_simulation *sim);

void				exit_coders(t_simulation *sim, int n);
void				exit_watcher(t_simulation *sim);
void				exit_monitor(t_simulation *sim);

/*
** ================= CLEAN & DESTROY =================
*/

void				clean_resource(t_simulation *sim);
void				clean_mutex_cond_simulation(t_simulation *sim);
void				destroy_mutex_prints(t_simulation *sim);

void				clean_coders(t_coder **c, int size);
void				destroy_mutex_cond_coders(t_coder **c, int size);

void				clean_dongles(t_dongle **d, int size);
void				clean_mutex_dongles(t_dongle **d, int size);

void				clean_queue(t_queue *q);
void				destroy_mutex_cond(t_mutex_cond *m);
void				free_2d_array(void **arr, int size);
#endif

/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   codexion.h										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: moerrais <moerrais@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/05/02 16:54:33 by moerrais		  #+#	#+#			 */
/*   Updated: 2026/06/29 16:11:26 by moerrais		 ###   ########.fr	   */
/*																			*/
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
	FINISHED,
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

typedef struct s_queue			t_queue;
typedef struct s_simulation		t_simulation;

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

typedef struct s_mutex_cond
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}	t_mutex_cond;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	bool			is_available;
	long long		cooldown_time;
	long long		last_release_time;
}	t_dongle;

typedef struct s_coder
{
	pthread_t		thread;
	int				id;
	bool			is_waiting_coder;
	long long		deadline;
	int				compilation_count;
	t_config		*config;
	long long		*time_start;
	pthread_mutex_t	*mutex_print;
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
	pthread_mutex_t	*is_finished_sim_m;
}	t_coder;

typedef struct s_queue
{
	t_coder			**coders;
	int				size;
	int				capacity;
	pthread_mutex_t	mutex_queue;
}	t_queue;

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
	int					finished_coders;
	pthread_mutex_t		finished_coders_m;
	bool				is_finished_sim;
	pthread_mutex_t		is_finished_sim_m;
}	t_simulation;

bool			parse_args(int ac, char **av,
					t_simulation *sim);
bool			validate_numeric_arguments(char **av);
bool			string_to_int(char **av, t_config *config);
bool			parser_time_val(char **av, t_config *config);
void			error_out_of_range(const char *arg, const char *val);
long			ft_atoi(char *str);

long long		get_time(void);
long long		get_time_since_program_start(t_coder *coder);
struct timespec	ft_get_time_add_time_wait(long long time_wait_ms);

void			ft_print_action(t_coder *coder, char *action);

bool			ft_init_simulation(int ac, char **av, t_simulation *sim);
bool			init_dongles(t_simulation *sim);
bool			init_coders(t_simulation *sim);
bool			ft_init_queue(t_simulation *sim);
bool			init_mutex_cond(t_mutex_cond *m);

void			init_coder_basic(t_simulation *sim, int i);
void			init_coder_shared(t_simulation *sim, int i);

bool			ft_start_simulation(t_simulation *sim);
void			run_scheduler_loop(t_simulation *sim);

void			*ft_coder_routine(void *arg);
void			*ft_watcher_routine(void *arg);
void			*ft_monitor_routine(void *arg);

bool			perform_coding(t_coder *coder);
bool			ft_sleep_coder(t_coder *coder, int state);
bool			ft_is_simulation_finished(t_coder *coder);

void			ft_stop_simulation(t_simulation *sim);
void			ft_stop_coders(t_coder **coders);
void			monitor_finished_simulation(t_simulation *sim);

void			pick_up_dongle(t_coder *coder);
void			return_dongles(t_coder *coder);
bool			is_valid_dongl_left_right(t_coder *coder);

void			push_priority_queue(t_coder *coder);
t_coder			*pop_queue(t_simulation *sim, t_scheduler scheduler);
void			enqueue_initial_coders(t_coder *coder);

void			shift_queue_elements(t_queue *q);
void			heapify_up(t_queue *q, int index);
void			heapify_down(t_queue *q, int parent);

int				parent_index(int index);
int				child_left_index(int index);
int				child_right_index(int index);

bool			is_same_deadline(t_coder *c1, t_coder *c2);
bool			is_greater(t_coder *c1, t_coder *c2);

t_watch_status	ft_get_status_watcher(t_simulation *sim);
bool			ft_check_coder_burnout(t_coder *coder);
bool			ft_is_finished_coder(t_coder *coder);
void			ft_is_burnout(bool *detected,
					pthread_mutex_t *detected_m);

void			join_threads(t_simulation *sim);
void			join_coders(t_simulation *sim, int n);
void			join_watcher(t_simulation *sim);
void			join_monitor(t_simulation *sim);

void			exit_coders(t_simulation *sim, int n);
void			exit_watcher(t_simulation *sim);
void			exit_monitor(t_simulation *sim);

void			ft_clean_resource(t_simulation *sim);

void			clean_mutex_cond_simulation(t_simulation *sim);
void			destroy_mutex_cond_coders(t_coder **c, int size);

void			clean_dongles(t_dongle **d, int size);
void			clean_mutex_dongles(t_dongle **d, int size);

void			clean_queue(t_queue *q);

void			destroy_mutex_cond(t_mutex_cond *m);
void			ft_free_double_array(void **arr, int size);

#endif
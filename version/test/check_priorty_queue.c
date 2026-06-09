# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <stdbool.h>
# include <limits.h>
typedef enum e_coder_status
{
	START,
	COMPILING,
	DEBUGGING,
	REFACTORING,
	FINISHED,
	IS_BURNOUT,
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
	ERROR_W
} t_watch_status;
typedef struct s_dongle
{
	bool			is_available;
	long long		cooldown_time;
	long long		last_release_time;
}	t_dongle;

typedef struct s_coder
{
	pthread_t		thread;
	int				id;
	bool			has_dongle;
	long long		deadline;


}	t_coder;

typedef struct s_dongle_request
{
	t_coder		*coder;
	long long	deadline;
}	t_dongle_request;

typedef struct s_queue
{
	t_dongle_request	**heap;
	int					size;
	int					capacity;
	long long			time_burnout;
}	t_queue;
typedef struct s_simulation
{
	pthread_t			monitor_tid;
	pthread_t			watcher_tid;

	pthread_mutex_t		mutex_print;

	long long			time_start;

	t_coder				**coders;

	t_queue				*queue;


	t_monitor_status	monitor_status;
	int					run_coders_counter;

	bool				is_watch_waiting;

	bool				is_burnout;
	pthread_mutex_t		burnout_mutex;
}	t_simulation;

t_watch_status	get_status_watcher(t_simulation *sim)
{
	t_watch_status	status;

	pthread_mutex_lock(&sim->watch_lock.mutex);
	status = sim->watch_status;
	pthread_mutex_unlock(&sim->watch_lock.mutex);
	return (status);
}

bool check_coder_burnout(t_simulation *sim, int i)
{
	bool burned = false;

	pthread_mutex_lock(&sim->coders[i]->mutex_cond.mutex);
	if (sim->coders[i]->deadline != 0 &&
		get_time() >= sim->coders[i]->deadline)
	{
		burned = true;
	}
	pthread_mutex_unlock(&sim->coders[i]->mutex_cond.mutex);

	if (burned)
	{
		print_coder_action(sim->coders[i], "is burnout");
		stop_monitor(sim);
		stop_coders(sim);
		return true;
	}
	return false;
}


void	detect_burnout_in_coders(t_simulation *sim)
{
	bool	ischeckboun;
	int		i;
	ischeckboun = false;
	while (!ischeckboun)
	{
		i = 0;
		if (get_status_watcher(sim) == FINISHED_W)
			break ;
		while (!ischeckboun && i < sim->config.number_of_coders)
		{
			if (get_status_watcher(sim) == FINISHED_W)
				break ;
			if (get_status_coder(sim->coders[i]) != FINISHED)
			{
				if (check_coder_burnout(sim, i))
					ischeckboun = true;
			}
			i++;
		}
		if (ischeckboun)
			break ;
	}
}
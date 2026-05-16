#include "codexion.h"

long long get_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000));
}

long long get_time_start_end(t_simulation *sim)
{
	long long time;

    pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
	time = get_time() - sim->time_start;
	pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
	return (time);
}	
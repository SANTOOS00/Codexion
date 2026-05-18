#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

long long get_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000));
// }
// struct timespec get_time_add_time_wait(long long time_wait_ms)
// {
//     struct timespec spec_ts;
//     struct timeval val_ts;
    
//     gettimeofday(&val_ts, NULL);

//     val_ts.tv_sec += time_wait_ms / 1000;
//     val_ts.tv_usec += (time_wait_ms % 1000) * 1000;
//     if (val_ts.tv_usec >= 1000000)
//     {
//         printf("is ok\n");
//         val_ts.tv_sec++;
//         val_ts.tv_usec -= 1000000;
//     }

//     spec_ts.tv_sec = val_ts.tv_sec;
//     spec_ts.tv_nsec = val_ts.tv_usec * 1000;
//     return (spec_ts);
// }
// int main()
// {

//     pthread_mutex_init(&mutex, NULL);
//     pthread_cond_init(&cond, NULL);
//     printf("%lld\n", get_time());
//     struct timespec time_wait = get_time_add_time_wait(200);
//     pthread_cond_timedwait(&cond, &mutex, &time_wait);
    
//     printf("%lld\n", get_time());

// }


// // #include "codexion.h"

// // void ft_fifo(t_queue **queue, t_config config)
// // {
	

// // 	return ;
// // }

// #define _POSIX_C_SOURCE 200809L  // ✅ مهم بزاف
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


int ready = 0;

void *worker(void *arg)
{
    sleep(3); // simulate work

    pthread_mutex_lock(&mutex);
    ready = 1;
    printf("Worker: signal sent\n");
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    pthread_t th;
    struct timeval ts;

    pthread_create(&th, NULL, worker, NULL);

    pthread_mutex_lock(&mutex);

    // نحسب الوقت الحالي + 2 ثواني
    gettimeofday(&ts, NULL);
    ts.tv_sec += 2;

    while (!ready)
    {
        int ret = pthread_cond_timedwait(&cond, &mutex, &ts);

        if (ret == ETIMEDOUT)
        {
            printf("Main: timeout! condition not met\n");
            break;
        }
    }

    if (ready)
        printf("Main: condition met\n");

    pthread_mutex_unlock(&mutex);

    pthread_join(th, NULL);
    return 0;
}


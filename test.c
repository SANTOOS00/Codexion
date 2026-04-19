#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
pthread_cond_t cond_producer;
pthread_cond_t cond_consumer;
pthread_mutex_t mutex;


typedef struct s_coder
{
        int id;
        pthread_t th;
        pthread_mutex_t mutex;
        pthread_cond_t cond;
        bool action;
} t_coder;





void *test(void *arg)
{
    t_coder *coder = (t_coder *)arg;
    
    printf("%p test \n", coder);
    // pthread_mutex_lock(&coder->mutex);
    // while (coder->action)
    // {
    //     printf("thread %d waiting\n", coder->id);
    //     pthread_cond_wait(&coder->cond, &coder->mutex);
    // }
    // pthread_mutex_unlock(&coder->mutex);
    
    // printf("thread %d woke up!\n", coder->id);
    return NULL;
}



void *manger(void *arg)
{
        t_coder *coders;
        coders = *(t_coder **)arg;
        int i = 0;
        printf("%p manger\n", coders);
        while(i < 10)
        {
                printf("manger step\n");
                if(i == 1)
                {
                    pthread_mutex_lock(&coders[i].mutex);
                    coders[i].action = false;
                    pthread_cond_broadcast(&coders[i].cond);
                    pthread_mutex_unlock(&coders[i].mutex);
                    
                }
                i++;
                usleep(1000);
        }
        return NULL;
}
int main(void)
{
    int     size = 10;
    t_coder **coders = malloc(sizeof(t_coder) * size);
    pthread_t manger_th;
    int i = 0;
    printf("%p main \n", coders);
    
    while (i < size)
    {
        printf("%p main in whila \n", &coders[i]);
        pthread_mutex_init(&coders[i].mutex, NULL);
        pthread_cond_init(&coders[i].cond, NULL);
        coders[i].action = true;
        coders[i].id = i;
        pthread_create(&coders[i].th, NULL, test, &coders[i]);
        i++;
    }

    pthread_create(&manger_th, NULL, manger, &coders);
    pthread_join(manger_th, NULL);


//     i = 0;
//     while (i < size)
//     {
//         // أوقف الthreads اللي ما تصحاش
//         pthread_mutex_lock(&coders[i].mutex);
//         coders[i].action = false;
//         pthread_cond_signal(&coders[i].cond);
//         pthread_mutex_unlock(&coders[i].mutex);
//         pthread_join(coders[i].th, NULL);
//         i++;
//     }
    free(coders);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// pthread_mutex_t lock;
int conut = 0;

void *task(void *arg)
{
    int *id = (int *)arg;
    // pthread_mutex_lock(&lock);
    while(conut < 2)
    {
		printf("number ==> %d", conut);
        printf("number thread => %d\n", *id);
        conut++;
		sleep(1);
    }
    // pthread_mutex_unlock(&lock);
    // free(arg); // مهم
    return NULL;
}

int main()
{
    pthread_t threads[2];
    // pthread_mutex_init(&lock, NULL);

    for(int i = 0; i < 2; i++)
    {
        // int *id = malloc(sizeof(int));
        // *id = i;
        pthread_create(&threads[i], NULL, task, &i);
	
    }

    for(int i = 0; i < 2; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // pthread_mutex_destroy(&lock);
    return 0;
}
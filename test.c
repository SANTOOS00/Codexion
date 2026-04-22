#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_coder
{
	pthread_cond_t cond;
	pthread_mutex_t mutex;
	int id;
	pthread_t thread;
}t_coder;

int i = 0;

void *test1(void *arg)
{
	t_coder *coder;

	i++;
	coder = (t_coder *)arg;
	printf("i = %d || id coder = %d\n", i, coder);
	return NULL;
}

int main()
{
	t_coder **coders;
	int i = 0;
	coders = malloc(sizeof(t_coder) * 5);
	while(i < 5)
	{
		coders[i] = malloc(sizeof(t_coder));
		pthread_mutex_init(&coders[i]->mutex, NULL);
		pthread_cond_init(&coders[i]->cond, NULL);
		coders[i]->id = i;
		i++;
	}
	i = 0;
	while(i < 5)
	{
		pthread_create(&coders[i]->thread, NULL, test1, &coders[i]);
		i++;
	}
	i = 0;
	while(i < 5)
	{
		pthread_join(coders[i]->thread, NULL);
		i++;
	}
	return 0;
}
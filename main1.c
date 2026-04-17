#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data{
	pthread_mutex_t *print;
}t_data;

typedef struct mainData
{
	t_data *coders;
	pthread_mutex_t print;
} mainData;

int NumOprint = 0;

void *ft_routine(void *args){
	t_data *coder = (t_data *)args;

	// pthread_mutex_lock(coder->print);
	while(NumOprint < 1000000000)
	{
		NumOprint++;
	}
	printf("number => %d", NumOprint);
	// printf("coder id = %d, Number of prints %d\n", coder->id, NumOprint);
	// pthread_mutex_unlock(coder->print);
	return (NULL);
}

void ft_create_coders(mainData *main){
	int num = main->num_coders;

	if (num < 0)
		return;
	main->coders = malloc(sizeof(t_data) * num);
	t_data *ret = main->coders;
	for (int i = 0; i < num; i++){	
		ret[i].id = i + 1;
		ret[i].print = &main->print;
		ret->creation_time = 0;
		if (pthread_create(&ret[i].coder, NULL, ft_routine, &ret[i]) != 0)
			return ;
	}
}

int main(int c, char **v){

	// 3, id, print id
	if (c != 2){
		return 0;
	}

	mainData main;

	main.num_coders = atoi(v[1]);

	if (pthread_mutex_init(&main.print, NULL) != 0)
		return (12);
	
	// allocate coders and create them
	ft_create_coders(&main);
	if (!main.coders)
		return (-1);

	// join thread and wait for cleanup
	for (int i = 0; i < main.num_coders; i++)
		if (pthread_join(main.coders[i].coder, NULL) != 0)
			return (1);

	pthread_mutex_destroy(&main.print);
	free(main.coders);
	return 0;
}
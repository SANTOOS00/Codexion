

#include "codexion.h"

void ft_fifo(t_queue **queue, t_config config)
{
	int i = 1;
    
	printf("id coder => %d  %p\n", queue[i]->coder->id, queue[i]->coder);
	printf("%d \n", queue[i]->coder->id);
    pthread_mutex_lock(&queue[i]->coder->mutex);
	queue[i]->coder->check_wait = false;
    pthread_mutex_unlock(&queue[i]->coder->mutex);
    pthread_cond_broadcast(&queue[i]->coder->cond);
	return ;
}

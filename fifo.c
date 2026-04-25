

#include "codexion.h"

void ft_fifo(t_queue **queue, t_config config)
{
	int i = 0;
	printf("%p \n", queue);
	while(queue[i])
	{
		printf("pointeur %d => %p\n", queue[i]->coder->id, queue[i]);
		i++;
	}
	return ;
}

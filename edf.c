
#include "codexion.h"

void ft_edf(t_queue **queue, t_config config)
{
	int i;
	printf("%p \n", queue);
	
	i = 0;
	while(queue[i])
	{
		printf("pointeur %d => %p\n", queue[i]->coder->id, queue[i]);
		i++;
	}
	return ;
}
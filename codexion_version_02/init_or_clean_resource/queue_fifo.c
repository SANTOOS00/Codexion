#include "../codexion.h"



void clean_queue_fifo(t_queue_fifo *queue_fifo)
{
	pthread_mutex_destroy(&queue_fifo->mutex_queue_fifo);
	free(queue_fifo->heap);
	free(queue_fifo);
}

t_queue_fifo *alloc_queue_fifo(int coders_number)
{
	t_queue_fifo *queue_fifo;

	queue_fifo = malloc(sizeof(t_queue_fifo));
	if (!queue_fifo)
		return (NULL);
	queue_fifo->heap = malloc(coders_number * sizeof(t_coder *));
	if (!queue_fifo->heap)
	{
		free(queue_fifo);
		return (NULL);
	}
	queue_fifo->size = 0;
	queue_fifo->capacity = coders_number;
	return (queue_fifo);
}


void print_data_queue(t_queue_fifo *fifo)
{
	int i;
	i = 0;
	while(i < fifo->capacity)
	{
		printf("id coder %d \n",  fifo->heap[i++]->id);
	}
}

bool ft_init_queue_fifo(t_simulation *sim)
{
	t_queue_fifo *q;
	
	q = alloc_queue_fifo(sim->config.number_of_coders);
	if (!q)
		return (false);
	if (pthread_mutex_init(&q->mutex_queue_fifo, NULL) != 0)
		return (free(q->heap), free(q), false);
	q->capacity = sim->config.number_of_coders;
	q->size = 0;
	sim->queue_fifo = q;
	return (true);
}
#include "../codexion.h"



void clean_queue_fifo(t_queue_fifo *queue_fifo)
{
	pthread_mutex_destroy(&queue_fifo->mutex_queue_fifo);
	free_2d_array((void **)queue_fifo->heap, queue_fifo->capacity);
	free(queue_fifo);
}

t_queue_fifo *alloc_queue_fifo(int coders_number)
{
	t_queue_fifo *queue_fifo;
	int			i;

	i = 0;
	queue_fifo = (t_queue_fifo *)malloc(sizeof(t_queue_fifo));
	if (!queue_fifo)
		return (NULL);
	queue_fifo->heap = (t_dongle_request **)malloc(sizeof(t_dongle_request *) * coders_number);
	if (!queue_fifo->heap)
		return (free(queue_fifo), false);
	while(i < coders_number)
	{
		queue_fifo->heap[i] = malloc(sizeof(t_dongle_request));
		if (!queue_fifo->heap[i])
		{
			free_2d_array((void **)queue_fifo->heap, i);
			free(queue_fifo);
			return (NULL);
		}
		i++;
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
	q->status_queue_fifo = START;
	sim->queue_fifo = q;
	return (true);
}
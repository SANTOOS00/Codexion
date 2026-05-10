#include "codexion.h"


int index_parent(int i)
{
	return ((i - 1) / 2);
}

void ft_swap(t_dongle_request **arg1, t_dongle_request **arg2)
{
	t_dongle_request *timp;
	timp = *arg1;
	*arg1 = *arg2;
	*arg2 = timp;
}



bool is_coder_ready(t_dongle_request *request)
{
	return ((request->coder->right_dongle->is_available 
		&& request->coder->left_dongle->is_available));
}

bool has_priority(t_dongle_request *req_a, t_dongle_request *req_b)
{
	bool a_ready;
	bool b_ready;

	a_ready = is_coder_ready(req_a);
	b_ready = is_coder_ready(req_b);
	if (a_ready && !b_ready)
		return (true);
	if (!a_ready && b_ready)
		return (false);
	if (req_a->deadline < req_b->deadline)
		return (true);
	return (false);
}

void heap_up(t_queue *q, int i)
{
	int parent;

	while (i > 0)
	{
		int parent = index_parent(i);
		if (has_priority(q->heap[i], q->heap[parent]))
		{
			q->heap[i]->coder->index_in_queue = parent;
			q->heap[parent]->coder->index_in_queue = i;
			ft_swap(&q->heap[i], &q->heap[parent]);
			i = parent;
		}
		else
			break;
	}
}


void heap_down(t_queue *q, int i)
{

}

t_dongle_request *pop(t_queue *q)
{
	pthread_mutex_lock(&q->mutex);
	// hat ba3d alfotor
	pthread_mutex_unlock(&q->mutex);
}


void push_queue(t_queue *queue, t_coder *coder)
{
	int i;

	pthread_mutex_lock(&queue->mutex);
	i = queue->size;
	queue->heap[i]->coder = coder;
	queue->heap[i]->deadline = coder->config->time_to_burnout + get_time();
	queue->size++;
	queue->heap[i]->coder->index_in_queue = i;
	heap_up(queue, i);	
	pthread_mutex_unlock(&queue->mutex);
}



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_heap
{
    int val;
    bool is_valid;
} t_heap;

typedef struct s_queue
{
    t_heap **arr;
    int size;
    int capacity;
} t_queue;

// 🔥 comparator
int is_greater(t_heap *a, t_heap *b)
{
    if (a->is_valid && !b->is_valid)
        return 1;
    if (!a->is_valid && b->is_valid)
        return 0;
    return (a->val > b->val);
}

void swap(t_heap **a, t_heap **b)
{
    t_heap *tmp = *a;
    *a = *b;
    *b = tmp;
}
    
void heapifyDown(t_queue *q, int i)
{
    while (1)
    {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < q->size && is_greater(q->arr[l], q->arr[largest]))
            largest = l;

        if (r < q->size && is_greater(q->arr[r], q->arr[largest]))
            largest = r;

        if (largest == i)
            break;

        swap(&q->arr[i], &q->arr[largest]);
        i = largest;
    }
}

void heapifyUp(t_queue *q, int i)
{
    if (i == 0)
        return;

    int parent = (i - 1) / 2;

    if (is_greater(q->arr[i], q->arr[parent]))
    {
        swap(&q->arr[i], &q->arr[parent]);
        heapifyUp(q, parent);
    }
}

// ✅ pop
t_heap *pop(t_queue *q)
{
    if (q->size == 0)
        return NULL;

    t_heap *top = q->arr[0];
    q->arr[0] = q->arr[q->size - 1];
    q->size--;

    heapifyDown(q, 0);
    return top;
}

// 🔥 update (المهم)
void update_node(t_queue *q, int index, bool new_valid)
{
    q->arr[index]->is_valid = new_valid;

    // صلح heap
    heapifyDown(q, index);
    heapifyUp(q, index);
}

// 🧪 print
void print_heap(t_queue *q)
{
    for (int i = 0; i < q->size; i++)
        printf("[%d,%d] ", q->arr[i]->val, q->arr[i]->is_valid);
    printf("\n");
}


// void swap(t_heap **a, t_heap **b)

// int is_greater(t_heap *a, t_heap *b)
// {
//     if (a->is_valid && !b->is_valid)
//         return 1;
//     if (!a->is_valid && b->is_valid)
//         return 0;
//     return (a->val > b->val);
// }


void push(t_heap *node, t_queue *q)
{
    int i = q->size;
    q->arr[i] = node;
    q->size++;

    while (i > 0)
    {
        int parent = (i - 1) / 2;

        if (is_greater(q->arr[i], q->arr[parent]))
        {
            swap(&q->arr[i], &q->arr[parent]);
            i = parent;
        }
        else
            break;
    }
}

int main()
{
    t_queue q;
    q.size = 3;
    q.capacity = 10;
    q.arr = malloc(sizeof(t_heap *) * q.capacity);

    // create nodes
    t_heap a = {20222, true};
    t_heap b = {500, true};
    t_heap c = {50, true};
    t_heap d_push = {100, true};

    q.arr[0] = &a;
    q.arr[1] = &b;
    q.arr[2] = &c;
    // q.arr[3] = &d;

    printf("Initial heap:\n");
    print_heap(&q);
	push(&d_push, &q);
    print_heap(&q);

    // 🔥 تغيير مهم
    printf("\nChange a -> valid = false\n");
    update_node(&q, 0, false);
	
    print_heap(&q);
	
    // // 🔥 pop
    printf("\nPOP:\n");
    update_node(&q, 3, true);
    t_heap *top = pop(&q);
    printf("Popped: [%d,%d]\n", top->val, top->is_valid);

    // print_heap(&q);

    return 0;
}





// #include "codexion.h"

// static int	index_parent(int i)
// {
// 	return ((i - 1) / 2);
// }

// static void	ft_swap(t_dongle_request **a, t_dongle_request **b)
// {
// 	t_dongle_request	*tmp;

// 	tmp = *a;
// 	*a = *b;
// 	*b = tmp;
// }

// static bool	can_run(t_dongle_request *req)
// {
// 	return (
// 		req->coder->left_dongle->is_available
// 		&& req->coder->right_dongle->is_available
// 	);
// }

// static bool	is_greater(t_dongle_request *a, t_dongle_request *b)
// {
// 	bool	a_ready;
// 	bool	b_ready;

// 	a_ready = can_run(a);
// 	b_ready = can_run(b);

// 	if (a_ready && !b_ready)
// 		return (true);
// 	if (!a_ready && b_ready)
// 		return (false);
// 	return (a->deadline < b->deadline);
// }

// void	heap_down(t_queue *queue, int i)
// {
// 	int	parent;
// 	int	left;
// 	int	right;

// 	while (1)
// 	{
// 		parent = i;
// 		left = (2 * i) + 1;
// 		right = (2 * i) + 2;

// 		if (left < queue->size
// 			&& is_greater(queue->heap[left], queue->heap[parent]))
// 			parent = left;

// 		if (right < queue->size
// 			&& is_greater(queue->heap[right], queue->heap[parent]))
// 			parent = right;

// 		if (parent == i)
// 			break ;

// 		queue->heap[i]->coder->index_in_queue = parent;
// 		queue->heap[parent]->coder->index_in_queue = i;

// 		ft_swap(&queue->heap[i], &queue->heap[parent]);

// 		i = parent;
// 	}
// }

// void	heap_up(t_queue *queue, int i)
// {
// 	int	parent;

// 	while (i > 0)
// 	{
// 		parent = index_parent(i);

// 		if (!is_greater(queue->heap[i], queue->heap[parent]))
// 			break ;

// 		queue->heap[i]->coder->index_in_queue = parent;
// 		queue->heap[parent]->coder->index_in_queue = i;

// 		ft_swap(&queue->heap[i], &queue->heap[parent]);

// 		i = parent;
// 	}
// }

// void	update_queue(t_queue *queue, int index)
// {
// 	pthread_mutex_lock(&queue->mutex);

// 	if (index > 0
// 		&& is_greater(queue->heap[index],
// 			queue->heap[index_parent(index)]))
// 		heap_up(queue, index);
// 	else
// 		heap_down(queue, index);

// 	pthread_mutex_unlock(&queue->mutex);
// }

// t_dongle_request	*pop(t_queue *queue)
// {
// 	t_dongle_request	*root;

// 	pthread_mutex_lock(&queue->mutex);

// 	if (queue->size == 0)
// 	{
// 		pthread_mutex_unlock(&queue->mutex);
// 		return (NULL);
// 	}

// 	if (!can_run(queue->heap[0]))
// 	{
// 		pthread_mutex_unlock(&queue->mutex);
// 		return (NULL);
// 	}

// 	root = queue->heap[0];

// 	if (queue->size == 1)
// 	{
// 		queue->size = 0;
// 		pthread_mutex_unlock(&queue->mutex);
// 		return (root);
// 	}

// 	queue->heap[0] = queue->heap[queue->size - 1];
// 	queue->heap[0]->coder->index_in_queue = 0;

// 	queue->size--;

// 	heap_down(queue, 0);

// 	pthread_mutex_unlock(&queue->mutex);

// 	return (root);
// }

// void	push_queue(t_queue *queue, t_coder *coder)
// {
// 	int	i;

// 	pthread_mutex_lock(&queue->mutex);

// 	i = queue->size;

// 	queue->heap[i]->coder = coder;
// 	queue->heap[i]->deadline =
// 		get_time() + coder->config->time_to_burnout;

// 	coder->index_in_queue = i;

// 	queue->size++;

// 	heap_up(queue, i);

// 	pthread_mutex_unlock(&queue->mutex);
// }
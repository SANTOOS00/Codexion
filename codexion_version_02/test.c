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
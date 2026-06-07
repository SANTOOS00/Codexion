# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_dongle
{
	bool			is_available;
	long long		cooldown_time;
	long long		last_release_time;
}	t_dongle;

typedef struct s_coder
{
	pthread_t		thread;
	int				id;
	bool			has_dongle;
	long long		deadline;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;

}	t_coder;

typedef struct s_dongle_request
{
	t_coder		*coder;
	long long	deadline;
}	t_dongle_request;

typedef struct s_queue
{
	t_dongle_request	**heap;
	int					size;
	int					capacity;
	long long			time_burnout;
}	t_queue;

long long	get_time(void)
{
	struct timeval	tv;
	long long		time_ms;

	gettimeofday(&tv, NULL);
	time_ms = (long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000;
	return (time_ms);
}

int	parent_index(int index)
{
	return ((index - 1) / 2);
}

int	cheld_left_index(int index)
{
	return ((2 * index) + 1);
}

int	cheld_right_index(int index)
{
	return ((2 * index) + 2);
}

bool	is_dongle_available(t_dongle *dongle)
{
	bool	success;
	if (!(get_time() - dongle->last_release_time >= dongle->cooldown_time))
	{
		return (false);
	}
	success = dongle->is_available;
	return (success);
}
bool	is_valid_dongl_left_right(t_coder *coder)
{
	return (is_dongle_available(coder->left_dongle)
		&& is_dongle_available(coder->right_dongle));
}


bool	is_greater(t_dongle_request *req1, t_dongle_request *req2)
{
	return (req1->deadline < req2->deadline);
}

bool	is_same_deadline(t_dongle_request *req1, t_dongle_request *req2)
{
	return (req1->deadline == req2->deadline);
}



void	ft_swap(t_dongle_request **s1, t_dongle_request **s2)
{
	t_dongle_request	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void	heapify_up(t_queue *q, int index)
{
	int	parent;

	while (index > 0)
	{
		parent = parent_index(index);
		if (is_greater(q->heap[index], q->heap[parent]))
        {
			ft_swap(&q->heap[index], &q->heap[parent]);
            index = parent; 
        }
		else if (is_same_deadline(q->heap[index], q->heap[parent])
			&& q->heap[index]->coder->id < q->heap[parent]->coder->id)
		{
			ft_swap(&q->heap[index], &q->heap[parent]);
			index = parent;
		}
		else
			break ;
	}
}

void	heapify_down(t_queue *q, int parent)
{
	int	cheld_left;
	int	cheld_right;
	int	index;

	while (parent < q->size)
	{
		cheld_left = cheld_left_index(parent);
		cheld_right = cheld_right_index(parent);
		index = parent;
		if (cheld_left < q->size && is_greater(q->heap[cheld_left],
				q->heap[parent]))
			index = cheld_left;
		if (cheld_right < q->size && is_greater(q->heap[cheld_right],
				q->heap[parent]))
			index = cheld_right;
		if (index == parent)
			break ;
		ft_swap(&q->heap[index], &q->heap[parent]);
		parent = index;
	}
}
t_coder	*pop_highest_priority_ready_coder(t_queue *q)
{
	int		i;
	int		best;
	t_coder	*coder;

	best = -1;
	i = 0;
	while (i < q->size)
	{
		if (is_valid_dongl_left_right(q->heap[i]->coder))
		{
			if (best == -1 || is_greater(q->heap[i], q->heap[best]))
				best = i;
		}
		i++;
	}
	if (best == -1)
		return (NULL);
	coder = q->heap[best]->coder;
	q->heap[best]->coder = q->heap[q->size - 1]->coder;
	q->heap[best]->deadline = q->heap[q->size - 1]->deadline;
	q->size--;
	heapify_down(q, best);
	heapify_up(q, best);
	return (coder);
}
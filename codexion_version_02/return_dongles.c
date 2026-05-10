/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_dongles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 17:11:31 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/09 17:55:43 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// bool is_greater(t_dongle_request *data_1, t_dongle_request *data_2)
// {
// 	if ((data_1->coder->right_dongle->is_available && data_1->coder->left_dongle->is_available) 
// 	    && !(data_2->coder->right_dongle->is_available && data_2->coder->left_dongle->is_available))
// 		return (true);
// 	if (!(data_1->coder->right_dongle->is_available && data_1->coder->left_dongle->is_available) 
// 	    && (data_2->coder->right_dongle->is_available && data_2->coder->left_dongle->is_available))
// 		return (false);
// 	if (data_1->deadline < data_2->deadline)
// 		return (true);
// 	return (false);
// }



// void push_queue(t_queue *queue, t_coder *coder)
// {
// 	// printf("push\n");
// 	int i;
// 	pthread_mutex_lock(&queue->mutex);

// 	i = queue->size;
// 	queue->heap[i]->coder = coder;
// 	queue->heap[i]->deadline = coder->config->time_to_burnout + get_time();
// 	queue->size++;
// 	pthread_mutex_unlock(&queue->mutex);

// 	while(i > 0)
// 	{
// 		pthread_mutex_lock(&queue->mutex);
// 		if (is_greater(queue->heap[i], queue->heap[(i - 1) / 2]))
// 		{
// 			ft_swap(&queue->heap[i], &queue->heap[index_parent(i)]);
// 			i = index_parent(i);
// 		}
// 		else 
// 		{
// 			pthread_mutex_unlock(&queue->mutex);
// 			break;
// 		}
// 		pthread_mutex_unlock(&queue->mutex);
// 	}	
// }

// void heapifyDown(t_queue *q, int i)
// {
//     while (1)
//     {
//         int largest = i;
//         int l = 2 * i + 1;
//         int r = 2 * i + 2;

//         if (l < q->size && is_greater(q->arr[l], q->arr[largest]))
//             largest = l;

//         if (r < q->size && is_greater(q->arr[r], q->arr[largest]))
//             largest = r;

//         if (largest == i)
//             break;

//         swap(&q->arr[i], &q->arr[largest]);
//         i = largest;
//     }
// }


// void heapifyUp(t_queue *q, int i)
// {
//     while (i > 0)
//     {
//         int parent = (i - 1) / 2;

//         if (is_greater(q->arr[i], q->arr[parent]))
//         {
//             swap(&q->arr[i], &q->arr[parent]);
//             i = parent; // نطلع للفوق
//         }
//         else
//         {
//             break; // وقف حيث البلاصة صحيحة
//         }
//     }
// }

// void update_node(t_queue *q, int index, bool new_valid)
// {
//     q->arr[index]->is_valid = new_valid;

//     // صلح heap
//     heapifyDown(q, index);
//     heapifyUp(q, index);
// }

void return_left_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->left_dongle->m_cn_dongle.mutex);
	(coder->left_dongle->is_available) = true;
	pthread_mutex_unlock(&coder->left_dongle->m_cn_dongle.mutex);
}

void return_right_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->right_dongle->m_cn_dongle.mutex);
	(coder->right_dongle->is_available) = true;
	pthread_mutex_unlock(&coder->right_dongle->m_cn_dongle.mutex);
}


void return_dongles(t_coder *coder)
{
	usleep(coder->left_dongle->cooldown_time * 1000);
	return_left_dongle(coder);	
	return_right_dongle(coder);
	// update_queue(coder->queue, *(coder->index_coder_left_queue));
	// update_queue(coder->queue, *(coder->index_coder_right_queue));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 16:54:58 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/02 18:21:25 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"


void push_queue(t_coder *coder)
{
    t_queue **queue;
    int i;

    i = 0;
    queue = initialize_queue(0);
    pthread_mutex_lock(queue[0]->mutex);
    while(queue[i]->index_coder != -1)
        i++;
    if(queue[i]->index_coder == -1)
        queue[i]->index_coder = coder->id;
    printf("%d\n", coder->id);
    pthread_mutex_unlock(queue[0]->mutex);
    return ;
}
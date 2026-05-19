/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_fifo_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:30:25 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/16 14:45:41 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"
t_monitor_status check_status_monitor(t_simulation *sim)
{
    t_monitor_status check_status;

    pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
    check_status = sim->monitor_status;
    pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
    return (check_status);
}

bool check_burnout(t_simulation *sim)
{
    bool check;

    pthread_mutex_lock(&sim->burnout_mutex);
    check = sim->is_burnout;
    pthread_mutex_unlock(&sim->burnout_mutex);
    return (check);
}

int check_size_queue(t_queue *queue)
{
    int size;
    
    pthread_mutex_lock(&queue->mutex_queue);
    size = queue->size;
    pthread_mutex_unlock(&queue->mutex_queue);
    return (size);
}

void    run_fifo_routine(t_simulation *sim)
{
    t_coder *coder;

    while (check_status_monitor(sim) != FINISHED_M)
    {
        add_queue_normal_to_queue(sim->queue_normal, sim->queue, FIFO);
        if (check_burnout(sim))
            break;
        coder = pop_queue(sim->queue, FIFO);
        if (!coder)
            usleep(500);
        else
        {
            pthread_mutex_lock(&coder->mutex_cond.mutex);
            coder->has_dongle = true;
            pthread_cond_broadcast(&coder->mutex_cond.cond);
            pthread_mutex_unlock(&coder->mutex_cond.mutex);
        }

    }
}

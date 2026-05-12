/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_fifo_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:30:25 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/12 20:19:51 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"


void    run_fifo_routine(t_simulation *sim)
{
    t_coder *coder;

    while (1)
    {
        pthread_mutex_lock(&sim->crossing->mutex_crossing);
        if (sim->crossing->size > 0)
            add_crossing_to_queue(sim->crossing, sim->queue, FIFO);
        pthread_mutex_unlock(&sim->crossing->mutex_crossing);

        coder = pop_queue(sim->queue, FIFO);
        
        if (coder)
        {
            pthread_mutex_lock(&coder->mutex_cond.mutex);
            coder->has_dongle = true;
            pthread_cond_broadcast(&coder->mutex_cond.cond);
            pthread_mutex_unlock(&coder->mutex_cond.mutex);
        }        
        else
            usleep(1000);
        pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
        if (sim->monitor_status == FINISHED_M)
            break;
        pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_fifo_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:30:25 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/13 14:46:25 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"



void update_burnout_timer(t_coder *coder, t_config config)
{
    coder->deadline = get_time() + config.time_to_burnout;
}



void    run_fifo_routine(t_simulation *sim)
{
    t_coder *coder;
    long long time_to_burnout;
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
            update_burnout_timer(coder, sim->config);
            coder->has_dongle = true;
            pthread_cond_broadcast(&coder->mutex_cond.cond);
            pthread_mutex_unlock(&coder->mutex_cond.mutex);
        }        
        else
            usleep(1000);
        pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
        if (sim->monitor_status == FINISHED_M || sim->is_burnout)
        {
            pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
            break;
        }
        pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
    }
}
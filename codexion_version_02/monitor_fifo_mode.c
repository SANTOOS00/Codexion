/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_fifo_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:30:25 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/14 20:18:09 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

bool check_burnout(t_simulation *sim)
{
    bool check;
    pthread_mutex_lock(&sim->burnout_mutex);
    check = sim->is_burnout;
    pthread_mutex_unlock(&sim->burnout_mutex);
    return (check);
}

t_monitor_status check_status_monitor(t_simulation *sim)
{
    t_monitor_status check_status;

    pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
    check_status = sim->monitor_status;
    pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
    return (check_status);
}


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
        if (sim->crossing->size)
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
        if (check_status_monitor(sim) == FINISHED_M || check_burnout(sim))
            break;
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:58:46 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/13 15:17:55 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



void istiy9ad_watch(t_simulation *sim)
{
    pthread_mutex_lock(&sim->watch_lock.mutex);
    sim->is_watch_waiting = true;
    pthread_cond_broadcast(&sim->watch_lock.cond);
	pthread_mutex_unlock(&sim->watch_lock.mutex);

}

void initiate_crossing_logic(t_simulation *sim)
{
    istiy9ad_watch(sim);
    pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
    sim->time_start = get_time();
    pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
    if (sim->config.scheduler == FIFO)
        run_fifo_routine(sim);
    if (sim->config.scheduler == EDF)
        run_edf_routine(sim);
}
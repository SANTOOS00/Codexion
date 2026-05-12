/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_fifo_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:30:25 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/12 18:19:08 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

void	run_fifo_routine(t_simulation *sim)
{
    t_coder_crossing *cor;
    usleep(1000);
    int size;
    cor = sim->crossing;
    while (1)
    {
        pthread_mutex_lock(&cor->mutex_crossing);
        size = cor->size;
        pthread_mutex_unlock(&cor->mutex_crossing);
        if (size > 0)
            add_crossing_to_queue(sim->crossing, sim->queue, FIFO);
        if(size == 0)
        {
            printf("finich crossing\n");
            break;
        }
    }
}
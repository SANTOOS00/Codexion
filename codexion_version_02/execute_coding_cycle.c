/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_coding_cycle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:37:14 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/13 17:01:13 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



bool get_is_burnout_monitor(t_simulation *sim)
{
    bool is_success;

    pthread_mutex_lock(&sim->burnout_mutex);
    is_success = sim->is_burnout;
    pthread_mutex_unlock(&sim->burnout_mutex);
    return (is_success);
}


void ft_compiling_coder(t_coder *coder)
{
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    coder->status = COMPILING;
	coder->compilation_count++;
    printf("%lld %d is compiling\n", get_time_start_end(coder->sim), coder->id);
    if (!get_is_burnout_monitor(coder->sim))
        usleep(coder->config->time_to_compile * 1000);
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void ft_debugging_coder(t_coder *coder)
{
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    coder->status = DEBUGGING;
    printf("%lld %d is debugging\n", get_time_start_end(coder->sim), coder->id);
    if (!get_is_burnout_monitor(coder->sim))
        usleep(coder->config->time_to_debug * 1000);
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void ft_refactoring_coder(t_coder *coder)
{
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    coder->status = REFACTORING;
    printf("%lld %d is refactoring\n", get_time_start_end(coder->sim), coder->id);
    if (!get_is_burnout_monitor(coder->sim))
        usleep(coder->config->time_to_refactor * 1000);
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void execute_coding_cycle(t_coder *coder)
{
	ft_compiling_coder(coder);
    return_dongles(coder);
	ft_debugging_coder(coder);
	ft_refactoring_coder(coder);
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    if (coder->compilation_count == coder->config->number_of_compiles_required)
        coder->status = FINISHED;
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

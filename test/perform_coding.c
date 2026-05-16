/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_coding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:37:14 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/16 12:50:11 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void ft_compiling_coder(t_coder *coder)
{
    pthread_mutex_lock(&coder->mutex_cond.mutex);
	coder->compilation_count++;
    printf("%lld %d is compiling\n", get_time_start_end(coder->sim), coder->id);
    usleep(coder->sim->config.time_to_compile * 1000);    
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void ft_debugging_coder(t_coder *coder)
{
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    printf("%lld %d is debugging\n", get_time_start_end(coder->sim), coder->id);
    usleep(coder->config->time_to_debug * 1000);
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void ft_refactoring_coder(t_coder *coder)
{
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    printf("%lld %d is refactoring\n", get_time_start_end(coder->sim), coder->id);
    usleep(coder->config->time_to_refactor * 1000);
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void perform_coding(t_coder *coder)
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

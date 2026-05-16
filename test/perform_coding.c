/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_coding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:37:14 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/16 16:09:53 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void print_coder_action(t_coder *coder, char *action)
{
    pthread_mutex_lock(&coder->sim->mutex_print);
    printf("%lld %d %s\n", get_time_start_end(coder->sim), coder->id, action);    
    pthread_mutex_unlock(&coder->sim->mutex_print);    
}

void ft_compiling_coder(t_coder *coder)
{
    pthread_mutex_lock(&coder->mutex_cond.mutex);
	coder->compilation_count++;
    print_coder_action(coder, "is compiling");
    usleep(coder->sim->config.time_to_compile * 1000);    
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void ft_debugging_coder(t_coder *coder)
{
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    print_coder_action(coder, "is debugging");
    usleep(coder->config->time_to_debug * 1000);
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void ft_refactoring_coder(t_coder *coder)
{
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    print_coder_action(coder, "is refactoring");
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

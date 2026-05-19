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

    long long time_wait;
    struct timespec time;

    time_wait = coder->config->time_to_compile;
    time = get_time_add_time_wait(time_wait);
    pthread_mutex_lock(&coder->mutex_cond.mutex);
	coder->compilation_count++;
    if (coder->status == IS_BURNOUT)
    {
        pthread_mutex_unlock(&coder->mutex_cond.mutex);
        return ;
    }
    print_coder_action(coder, "is compiling");
    pthread_cond_timedwait(&coder->mutex_cond.cond, 
        &coder->mutex_cond.mutex, &time);   
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void ft_debugging_coder(t_coder *coder)
{
    long long time_wait;
    struct timespec time;

    time_wait = coder->config->time_to_debug;
    time = get_time_add_time_wait(time_wait);
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    if (coder->status == IS_BURNOUT)
    {
        pthread_mutex_unlock(&coder->mutex_cond.mutex);
        return ;
    }
    print_coder_action(coder, "is debugging");
    pthread_cond_timedwait(&coder->mutex_cond.cond, 
        &coder->mutex_cond.mutex, &time);
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
    }
    
void ft_refactoring_coder(t_coder *coder)
    {
        
    long long time_wait;
    struct timespec time;

    time_wait = coder->config->time_to_refactor;
    time = get_time_add_time_wait(time_wait);
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    if (coder->status == IS_BURNOUT)
    {
        pthread_mutex_unlock(&coder->mutex_cond.mutex);
        return ;
    }
    print_coder_action(coder, "is refactoring");
    pthread_cond_timedwait(&coder->mutex_cond.cond, 
        &coder->mutex_cond.mutex, &time);
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void perform_coding(t_coder *coder)
{
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    if (coder->status == IS_BURNOUT)
    {
        pthread_mutex_unlock(&coder->mutex_cond.mutex);
        return ;
    }
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
	ft_compiling_coder(coder);
    return_dongles(coder);
	ft_debugging_coder(coder);
	ft_refactoring_coder(coder);
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    if (coder->compilation_count == coder->config->number_of_compiles_required)
        coder->status = FINISHED;
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

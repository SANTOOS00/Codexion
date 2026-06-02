/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 22:16:27 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/02 22:16:35 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

long long get_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000));
}

long long get_time_start_end(t_simulation *sim)
{
	long long time;

    pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
	time = get_time() - sim->time_start;
	pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
	return (time);
}

struct timespec get_time_add_time_wait(long long time_wait_ms)
{
    struct timespec spec_ts;
    struct timeval val_ts;
    
    gettimeofday(&val_ts, NULL);

    val_ts.tv_sec += time_wait_ms / 1000;
    val_ts.tv_usec += (time_wait_ms % 1000) * 1000;
    if (val_ts.tv_usec >= 1000000)
    {
        val_ts.tv_sec++;
        val_ts.tv_usec -= 1000000;
    }

    spec_ts.tv_sec = val_ts.tv_sec;
    spec_ts.tv_nsec = val_ts.tv_usec * 1000;
    return (spec_ts);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 22:16:27 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/05 19:58:35 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

long long	get_time(void)
{
	struct timeval	tv;
	long long		time_ms;

	gettimeofday(&tv, NULL);
	time_ms = (long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000;
	return (time_ms);
}

long long	get_time_start_end(t_simulation *sim)
{
	long long	time;

	pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
	time = get_time() - sim->time_start;
	pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
	return (time);
}

struct timespec	get_time_add_time_wait(long long time_wait_ms)
{
	struct timespec	spects;
	struct timeval	valts;

	gettimeofday(&valts, NULL);
	valts.tv_sec += time_wait_ms / 1000;
	valts.tv_usec += (time_wait_ms % 1000) * 1000;
	if (valts.tv_usec >= 1000000)
	{
		valts.tv_sec++;
		valts.tv_usec -= 1000000;
	}
	spects.tv_sec = valts.tv_sec;
	spects.tv_nsec = valts.tv_usec * 1000;
	return (spects);
}

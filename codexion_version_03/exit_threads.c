/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:46:14 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/14 15:46:55 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



// void exit_monitor_tid(t_simulation *sim)
// {
// 	pthread_mutex_lock(&sim->coders_cnt_lock.mutex);
// 	sim->monitor_status = ERROR_M;
// 	pthread_cond_broadcast(&sim->coders_cnt_lock.cond);
// 	pthread_mutex_unlock(&sim->coders_cnt_lock.mutex);
// 	join_monitor(sim);
// }


// void exit_watcher_tid(t_simulation *sim)
// {
// 	pthread_mutex_lock(&sim->watch_lock.mutex);
// 	sim->watch_status = ERROR_W;
// 	pthread_cond_broadcast(&sim->watch_lock.cond);
// 	pthread_mutex_unlock(&sim->watch_lock.mutex);
// }

// void exit_thread(t_simulation *sim, int size_threads_create)
// {
// 	int i;
	
// 	i = 0;
// 	while(i < size_threads_create)
// 	{
// 		pthread_mutex_lock(&sim->coders[i]->coders_cnt_lock->mutex);
// 		sim->coders[i]->status = ERROR;
// 		pthread_cond_broadcast(&sim->coders[i]->coders_cnt_lock->cond);
// 		pthread_mutex_unlock(&sim->coders[i]->coders_cnt_lock->mutex);
// 		i++;
// 	}
// 	join_coders(sim, size_threads_create);
// }
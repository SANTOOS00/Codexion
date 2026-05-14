/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_coder_workflow.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:50:54 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/14 11:58:22 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


t_coder_status get_stataus_coder(t_coder *coder)
{
	t_coder_status status;
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	status = coder->status;
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
	return (status);
}

void enqueue_coder_request(t_coder *coder)
{
	if (coder->status == START && coder->id % 2 != 0)
		usleep(1000);
	push_crossing(coder);
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	coder->has_dongle = false;
    while (!coder->has_dongle)
		pthread_cond_wait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex);
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
	if(get_stataus_coder(coder) == ERROR)
		return ;
}

void works_coders_threads(t_coder *coder)
{
	
	while(!get_is_burnout_monitor(coder->sim) && get_stataus_coder(coder) != FINISHED && get_stataus_coder(coder) != ERROR)
	{
		enqueue_coder_request(coder);
		if (get_stataus_coder(coder) == ERROR)
			break;
		execute_coding_cycle(coder);
	}
}
bool execute_coder_workflow(t_coder *coder)
{
	works_coders_threads(coder);
	return (true);
}
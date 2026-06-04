/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_main_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:50:54 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/04 21:00:16 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void	update_burnout_timer(t_coder *coder, t_config config)
{
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	coder->deadline = get_time() + config.time_to_burnout;
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

t_coder_status	get_status_coder(t_coder *coder)
{
	t_coder_status	status;

	pthread_mutex_lock(&coder->mutex_cond.mutex);
	status = coder->status;
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
	return (status);
}

void	enqueue_coder_request(t_coder *coder)
{
	if (get_status_coder(coder) == START && coder->id % 2 != 0)
		usleep(1000);
	push_normal_queue(coder);
	printf("push coder id %d\n", coder->id);
	if (get_status_coder(coder) == IS_BURNOUT)
		return ;
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	coder->has_dongle = false;
	while (!coder->has_dongle)
		pthread_cond_wait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex);
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void	coder_main_loop(t_coder *coder)
{
	printf("id coder %d\n", coder->id);
	update_burnout_timer(coder, *coder->config);
	while (1)
	{
		if (get_status_coder(coder) == FINISHED)
			break ;
		enqueue_coder_request(coder);
		if (get_status_coder(coder) == IS_BURNOUT)
			break ;
		update_burnout_timer(coder, *coder->config);
		pick_up_dongle(coder);
		perform_coding(coder);
	}
}
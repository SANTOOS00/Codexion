/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manger_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:40:21 by username          #+#    #+#             */
/*   Updated: 2026/04/15 23:00:04 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*rutune(void *args)
{
	t_data_thread	data_thread;
}

int	manger_threads(t_config config)
{
	int					i;
	t_data_thread		*th;
	t_manger_threads	*mng_coders;

	i = 0;
	mng_coders = (t_manger_threads *) malloc(sizeof(t_manger_threads));
	if (!mng_coders)
	{
		manger_malloc(FREE);
		return (NULL);
	}
	mng_coders->coders = malloc(sizeof(t_data_thread) * config.number_of_coders);
	if (!mng_coders)
	{
		manger_malloc(FREE);
		return (NULL);
	}
	i = 0;
	while (config.number_of_coders > i)
	{
		th = &mng_coders->coders[i];
		th->mutex = &mng_coders->mutex;
		th->mutex = &mng_coders->cond;
		if (create_thread(&th->coder, NULL, &rutune, &th))
		{
			manger_malloc(FREE);
			return (NULL);
		}
		i++;
	}
	i = 0;
	while (config.number_of_coders > i)
	{
		th = &mng_coders->coders[i];
		pthread_join(th->coder, NULL);
	}
}

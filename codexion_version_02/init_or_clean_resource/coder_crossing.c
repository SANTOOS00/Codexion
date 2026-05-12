/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_crossing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:47:02 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/12 20:37:15 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"



static void  free_2d_arrays(t_coder **heap, int size)
{
	int i;

	i = 0;
	while (i < size)
		free(heap[i++]);
	free(heap);
}

void clean_crossing(t_coder_crossing *crossing)
{
    pthread_mutex_destroy(&crossing->mutex_crossing);
	free(crossing->heap);
    free(crossing);
}

t_coder_crossing *alloc_coder_crossing(int coders_number)
{
	t_coder_crossing *coder_crossing;

	coder_crossing = (t_coder_crossing *)malloc(sizeof(t_coder_crossing));
	if (!coder_crossing)
		return (NULL);
	coder_crossing->heap = (t_coder **)malloc(sizeof(t_coder *) * coders_number);
	if (!coder_crossing->heap)
	{
		free(coder_crossing);
		return (NULL);
	}

	coder_crossing->size = 0;
	coder_crossing->capacity = coders_number;
	return (coder_crossing);
}

bool ft_init_coder_crossing(t_simulation *sim)
{
	t_coder_crossing *crossing;

	crossing = alloc_coder_crossing(sim->config.number_of_coders);
	if (!crossing)
		return (false);
	if (pthread_mutex_init(&crossing->mutex_crossing, NULL) != 0)
	{
		free_2d_array((void **)crossing->heap, crossing->capacity);
		free(crossing);
		return (false);
	}
	crossing->capacity = sim->config.number_of_coders;
	crossing->size = 0;
	sim->crossing = crossing;
	return (true);
}
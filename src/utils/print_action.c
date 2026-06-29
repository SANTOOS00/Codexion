/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 03:03:29 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/29 00:58:35 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	ft_print_action(t_coder *coder, char *action)
{
	long	time;

	time = get_time_since_program_start(coder);
	pthread_mutex_lock(coder->mutex_print);
	printf("%ld %d %s\n", time, coder->id, action);
	pthread_mutex_unlock(coder->mutex_print);
}

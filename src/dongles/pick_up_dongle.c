/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_up_dongle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 17:11:45 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/29 15:36:05 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	pick_up_left_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->left_dongle->mutex);
	(coder->left_dongle->is_available) = false;
	pthread_mutex_unlock(&coder->left_dongle->mutex);
	ft_print_action(coder, "has taken a dongle");
}

void	pick_up_right_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->right_dongle->mutex);
	(coder->right_dongle->is_available) = false;
	pthread_mutex_unlock(&coder->right_dongle->mutex);
	ft_print_action(coder, "has taken a dongle");
}

void	pick_up_dongle(t_coder *coder)
{
	if (ft_is_simulation_finished(coder))
		return ;
	pick_up_left_dongle(coder);
	pick_up_right_dongle(coder);
}

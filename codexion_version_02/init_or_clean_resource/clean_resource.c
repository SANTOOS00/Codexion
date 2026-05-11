/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_resource.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 04:05:58 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/11 11:48:16 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void clean_resource(t_simulation *simulation)
{
	clean_dongles(simulation->dongles, simulation->config.number_of_coders);
	clean_mutex_cond_simulation(simulation);
	clean_queue_pro(simulation->queue_priority);
	clean_coders(simulation->coders, simulation->config.number_of_coders);
	clean_queue_fifo(simulation->queue_fifo);
}

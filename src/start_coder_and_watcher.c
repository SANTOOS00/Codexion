/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_coder_and_watcher.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 21:06:44 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/04 21:10:06 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void start_coder_and_watcher(t_simulation *sim)
{
	usleep(1000);
	activate_coders(sim);
	activate_watcher(sim);
	init_time_start(sim);
	run_fifo_or_edf_routine(sim);
}
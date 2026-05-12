/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:58:46 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/12 16:16:19 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void initiate_crossing_logic(t_simulation *sim)
{
    if (sim->config.scheduler == FIFO)
        run_fifo_routine(sim);
    if (sim->config.scheduler == EDF)
        run_edf_routine(sim);
}
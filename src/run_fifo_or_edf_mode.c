/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_fifo_or_edf_mode.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 22:12:53 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/02 22:13:43 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

void    run_fifo_or_edf_routine(t_simulation *sim)
{
    if(sim->config.scheduler == FIFO)
        run_fifo_routine(sim);
    else if (sim->config.scheduler == EDF)
        run_edf_routine(sim);
}
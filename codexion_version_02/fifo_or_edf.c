/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo_or_edf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 03:50:54 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/06 04:01:05 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


bool ft_edf(t_simulation *sim)
{
	
	return (true);
}


bool ft_fifo(t_simulation *sim)
{
	return (true);
}


bool ft_fifo_or_edf(t_simulation *sim)
{
	if (sim->config.scheduler == FIFO)
		ft_fifo(sim);
	else if(sim->config.scheduler == EDF)
		ft_edf(sim);
	return (true);
}

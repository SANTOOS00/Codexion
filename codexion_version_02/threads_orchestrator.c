/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_orchestrator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 22:11:10 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/06 03:42:18 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"





bool start_simulation(t_simulation *sim)
{
	if (run_monitor_simulation(sim) == false)	
		return (clean_resource(sim), false);
	if (start_coders_in_simulation(sim) == false)
		return (clean_resource(sim), false);	
	return (true);
		
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:59:05 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/23 06:05:11 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <pthread.h>

static void	reset_simulation_vars(t_simulation *sim);
static bool	ft_set_simulation_intial_state(int argc, char **argv,
		t_simulation *simulation);

bool	ft_init_simulation(int argc, char **argv, t_simulation *simulation)
{
	if (!ft_set_simulation_intial_state(argc, argv, simulation))
		return (false);
	if (!init_dongles(simulation))
	{
		clean_mutex_cond_simulation(simulation);
		return (false);		
	}
	if (!ft_init_queue(simulation))
	{
		clean_mutex_cond_simulation(simulation);
		clean_coders(simulation->coders, simulation->config.number_of_coders);
		return (false);
	}
	if (!init_coders(simulation))
	{
		
		clean_coders(simulation->coders, simulation->config.number_of_coders);
		clean_dongles(simulation->dongles, simulation->config.number_of_coders);
		clean_mutex_cond_simulation(simulation);
		return (false);
	}
	return (true);
}

static void	reset_simulation_vars(t_simulation *sim)
{
	sim->run_coders_counter = 0;
	sim->monitor_status = START_M;
	sim->time_start = 0;
	sim->is_watch_waiting = false;
	sim->watch_status = START_W;
	sim->finished_coders = 0;
	sim->is_finished_sim = false;
}

void	clean_mutex_cond_simulation(t_simulation *simulation)
{
	destroy_mutex_cond(&simulation->monitor_mu_cond);
	destroy_mutex_cond(&simulation->watch_mu_cond);
	pthread_mutex_destroy(&simulation->is_finished_sim_m);
	pthread_mutex_destroy(&simulation->finished_coders_m);
	pthread_mutex_destroy(&simulation->mutex_print);
}

static bool	ft_set_simulation_intial_state(int argc, char **argv,
		t_simulation *simulation)
{
	if (!parse_args(argc, argv, simulation))
		return (false);
	if (!init_mutex_cond(&simulation->monitor_mu_cond))
		return (false);
	if (!init_mutex_cond(&simulation->watch_mu_cond))
	{
		destroy_mutex_cond(&simulation->monitor_mu_cond);
		return (false);
	}
	if (pthread_mutex_init(&simulation->mutex_print, NULL) != 0)
	{
		destroy_mutex_cond(&simulation->monitor_mu_cond);
		destroy_mutex_cond(&simulation->watch_mu_cond);
		return (false);
	}
	if (pthread_mutex_init(&simulation->is_finished_sim_m, NULL) != 0) 
	{
		destroy_mutex_cond(&simulation->monitor_mu_cond);
		destroy_mutex_cond(&simulation->watch_mu_cond);
		pthread_mutex_destroy(&simulation->mutex_print);
		return (false);
	}
	if (pthread_mutex_init(&simulation->finished_coders_m, NULL) != 0)
	{
		destroy_mutex_cond(&simulation->monitor_mu_cond);
		destroy_mutex_cond(&simulation->watch_mu_cond);
		pthread_mutex_destroy(&simulation->mutex_print);
		pthread_mutex_destroy(&simulation->is_finished_sim_m);
		return (false);
	}
	reset_simulation_vars(simulation);
	return (true);
}

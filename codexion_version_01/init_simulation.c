/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_coders.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 16:54:48 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/02 18:40:43 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


bool ft_set_simulation_intial_state(char **argv, int argc, t_simulation *simulation) {
    simulation->is_burnout = false;
    simulation->coders_counter = 0;
    if (!parse_args(argc, argv, &simulation->config))
        return (false);
    if (!ft_init_mutex_cond_var(&simulation->coders_counter_m_c))
        return false;
    if (!pthread_mutex_init(&simulation->burnout_mutex, NULL))
        return (ft_destrory_mutex_cond_var(&simulation->coders_counter_m_c), false);
    if (!pthread_mutex_init(&simulation->print_mutex, NULL)) {
        pthread_mutex_destroy(&simulation->burnout_mutex);
        ft_destrory_mutex_cond_var(&simulation->coders_counter_m_c);
        return false;
    }
    return true;
}

void ft_clean_simulation_initial_state(t_simulation *simulation) {
    ft_destrory_mutex_cond_var(&simulation->coders_counter_m_c);
    pthread_mutex_destroy(&simulation->burnout_mutex);
    pthread_mutex_destroy(&simulation->print_mutex);
}




bool ft_init_simulation(char **argv, int argc, t_simulation *simulation)
{
    if (!ft_set_simulation_intial_state(argv, argc, simulation))
        return (false);

    if (!ft_init_dongles(simulation))
        return (ft_clean_simulation_initial_state(simulation), false);

    if (!ft_init_coders(simulation))
    {
        ft_clean_simulation_initial_state(simulation);
        ft_clean_dongles(simulation);
        return false;
    }
    return (true);
}
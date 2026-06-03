/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:19:23 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/03 17:00:21 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

bool    parse_args(int ac, char **av, t_config *config)
{
    if (ac != 9)
    {
        fprintf(stderr,
            "./codexion [number_of_coders] "
            "[time_to_burnout] [time_to_compile] "
            "[time_to_debug] [time_to_refactor] "
            "[number_of_compiles_required] [dongle_cooldown] \n");
        return (false);
    }
    return (false);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 16:37:06 by santoos           #+#    #+#             */
/*   Updated: 2026/04/12 00:51:06 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
int parse_args(int argc, char **argv, t_config *config)
{
    (void)argc;
    (void)**argv;
    config->number_of_coders = 4;
    config->time_to_burnout = 200;
    config->time_to_compile = 200;
    config->time_to_debug = 200;
    config->time_to_refactor = 200;
    config->number_of_compiles_required = 200;
    config->dongle_cooldown = 200;
    config->scheduler = FIFO;
    return 0;
}

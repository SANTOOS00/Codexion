/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 16:37:06 by santoos           #+#    #+#             */
/*   Updated: 2026/04/09 17:09:24 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
int parse_args(int argc, char **argv, t_config *config)
{
    (void)argc;
    (void)**argv;
    config->number_of_coders = 8;
    config->time_to_burnout = 200;
    config->time_to_compile = 200;
    config->time_to_debug = 200;
    config->time_to_refactor = 200;
    config->number_of_compiles_required = 200;
    config->dongle_cooldown = 200;
    config->scheduler = EDF;
    return 0;
}
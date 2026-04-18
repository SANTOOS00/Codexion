/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:23:19 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/18 02:46:15 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int parse_args(int argc, char **argv, t_config *config)
{
    (void)argc;
    (void)**argv;
    config->number_of_coders = 4;
    config->time_to_burnout = 200;
    config->time_to_compile =10;
    config->time_to_debug = 10;
    config->time_to_refactor = 10;
    config->number_of_compiles_required = 10;
    config->dongle_cooldown = 10;
    config->scheduler = FIFO;	
    return 0;
}

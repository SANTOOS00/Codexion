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


bool parse_number_of_coders(char **argv, t_config *config)
{
    long val;

    val = ft_atoi(argv[1]);
    if (val == -1)
        return (false);
    if (val == 0)
        return (false);
    config->number_of_coders = val;
    return (true);
}

bool string_to_int(char **argv, t_config *config)
{
    if (parse_number_of_coders(argv, config) == false)
    {
        fprintf(stderr,
                "Error: 'number_of_coders' must be between 1 and INT_MAX (got '%s').\n",
                argv[1]);
        return (false);
    }
    if (parser_time_val(argv, config) == false)
        return (false);
    if (parse_required_compiles(argv, config) == false)
        return (false);
    return (true);
}

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



long ft_atio(char *string_number)
{
    int i;
    long res;
    int digit;

    i = 0;
    res = 0;
    if (string_number[i] == '+')
        i++;
    // while (string_number[i] != '\0')
    // {
    //     digit = string_number[i] - '0';
    //     if (res > (INT_MAX - digit) / 10)
    //         return (-1);
    //     res = 10 * res + (string_number[i] - '0');
    //     i++;
    // }
    return (res);
}

bool parser_number_of_coders(char **args, t_config *config)
{
    long val;

    val = ft_atio(args[1]);
    if (val == -1)
        return (false);
    // if (val == 0)
    // {
    //     return (false);
    // }
    printf("Ss\n");
    config->number_of_coders = val;
    return (true);
}

bool string_to_int(char **args, t_config *config)
{
    t_config *config_parser;
    if (parser_number_of_coders(args, config) == false)
        return (false);
    // printf("%ld\n", config->number_of_coders);
    // config->number_of_coders = config_parser->number_of_coders;
    return (true);
}

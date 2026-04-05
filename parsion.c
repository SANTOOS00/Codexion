/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsion.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 03:32:29 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/05 16:25:44 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// int ft_isdigit(char c)
// {
//     if (c >= 48 && c <= 57)
//         return 0;
//     return 1;
// }
// void save_data(t_config *data_config)
// {
//     data_config->number_of_coders = 12
// }
int parsion(int argc, char **argv, t_config *config)
{
    config->number_of_coders = 2;
    config->time_to_burnout = 100;
    config->time_to_compile = 100;
    config->time_to_debug = 12;
    config->time_to_refactor = 12;
    config->number_of_compiles_required = 12;
    config->dongle_cooldown = 12;
    config->scheduler = FIFO;
    return 0; 
    // int i = 1;
    // while(i < 9)
    // {
    //     char *arg = argv[i];
    //     int j = 0;
    //     if (arg[j] == '-' || arg[i] == '+')
    //         j++;
    //     while(arg[j] != '\0')
    //     {
    //         if(ft_isdigit(arg[j]))
    //             return (1);
    //         j++;
    //     }
    //     i++;
    // }
    // save_data(data_config)
    // return(0);   
}
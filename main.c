/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 03:32:23 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/02 05:10:07 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "codexion.h"


int main(int argc, char **argv)
{
    // t_config config;
    int i = 1;
    if(argc != 9)
    {
        write(2, "Error: invalid number of arguments\n", 35);
        return(1);
    }
    if(parsion(argv))
    {
        write(2, "Error: invalid number of arguments\n", 35);
        return(1);
    }
    printf("not error");
    // config.number_of_coders = atoi(argv[1]);
    // config.time_to_burnout = atoi(argv[2]);
    // config.time_to_compile = atoi(argv[3]);
    // config.time_to_debug = atoi(argv[4]);
    // config.time_to_refactor = atoi(argv[5]);
    // config.number_of_compiles_required = atoi(argv[6]);
    // config.dongle_cooldown = atoi(argv[6]);
}

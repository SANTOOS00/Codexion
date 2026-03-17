/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 22:12:07 by santoos           #+#    #+#             */
/*   Updated: 2026/03/17 22:26:47 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


int main(int argc, char **argv)
{
    t_config config;
    int i = 1;
    if(argc != 9)
    {
        write(2, "Error: invalid number of arguments\n", 35);
        return(1);
    }
    while(i < 7)
    {
        // argv[i] = atoi(argv[i])
        printf("argv ==> %d", atoi(argv[i]));
        i++;
    }
}
// config.number_of_coders = atoi(argc)
// config.time_to_burnout;
// config.time_to_compile;
// config.time_to_debug;
// config.time_to_refactor;
// config.number_of_compiles_required;
// config.dongle_cooldown;
// config.scheduler;
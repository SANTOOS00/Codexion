/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 22:12:07 by santoos           #+#    #+#             */
/*   Updated: 2026/03/23 01:36:25 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>
#include <ctype.h>


int main(int argc, char **argv)
{
    t_config config;
    int i = 1;
    if(argc != 9)
    {
        write(2, "Error: invalid number of arguments\n", 35);
        return(1);
    }
    
    // while(i < 7)
    // {
        // argv[i] = atoi(argv[i])
        // int res = ;
        // int *tab_res;
        // int res = ;
    for(int i = 1; i < 9;i++)
    {
        char *arg = argv[i];
        for(int j = 0; arg[j] != '\0'; j++)
        {
            if (!isdigit(arg[j]))
            return (1);
        }
        printf("%s\n", arg);
    }
    config.number_of_coders = atoi(argv[1]);
    config.time_to_burnout = atoi(argv[2]);
    config.time_to_compile = atoi(argv[3]);
    config.time_to_debug = atoi(argv[4]);
    config.time_to_refactor = atoi(argv[5]);
    config.number_of_compiles_required = atoi(argv[6]);
    config.dongle_cooldown = atoi(argv[6]);
    printf("%d\n", config.dongle_cooldown);
        // printf("res ===> %d\n",res); 
        // tab_res[0] = res;
        // if(tab_res[0] == NULL)
        // {
        //     write(2, "Error: invalid number of arguments\n", 35);
        //     return(1);
        // }
        // printf("argv ==> %s\n", res);
        // i++;
    // }
}
// config.number_of_coders = atoi(argc)
// config.time_to_burnout;
// config.time_to_compile;
// config.time_to_debug;
// config.time_to_refactor;
// config.number_of_compiles_required;
// config.dongle_cooldown;
// config.scheduler;
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 03:32:23 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/05 17:38:54 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "codexion.h"
int 
void *routine()
{
    mutex_lock;
    int i = 0;
    printf("test from  threads \n");
    conut++;
    i++;
    mutex_unlock;
}
int main(int argc, char **argv)
{
    int i, j;
    i = 0;
    j = 0;
    t_config data_config;
    parsion(argc, argv, &data_config);
    
    pthread_t threads[data_config.number_of_coders];
    while(data_config.number_of_coders > i)
    {
        printf("%d", pthread_create(&threads[i], NULL, &routine, NULL));
        i++;
    }
    while(data_config.number_of_coders > j)
    {
        printf("%d", pthread_join(threads[j], NULL));
        j++;
    }
    return 0;
}
// int ft_isdigit(char c)
// {
//     if (c >= '0' && c <= '9')
//         return 1;
//     return 0;
// }

// void save_data(char **argv, t_config *data_config)
// {
//     data_config->number_of_coders = ft_atoi_int(argv[0]);
//     data_config->time_to_burnout = ft_atoi_long(argv[1]);
//     if (strcmp(argv[8], "FIFO") == 0)
//         data_config->scheduler = FIFO;
//     else if (strcmp(argv[8], "EDF") == 0)
//         data_config->scheduler = EDF;
// }

// int parsion(char **argv, t_config *data_config)
// {
//     int i = 1;
//     while(i < 9)
//     {
//         char *arg = argv[i];
//         int j = 0;
//         if (arg[j] == '-' || arg[j] == '+')
//             j++;
//         while(arg[j] != '\0')
//         {
//             if(!ft_isdigit(arg[j]))  // ملاحظة: invalid if not digit
//                 return 1;
//             j++;
//         }
//         i++;
//     }
//     save_data(argv, data_config);
//     return 0;
// }

// if(argc != 9)
// {
//     write(2, "Error: invalid number of arguments\n", 35);
//     return 1;
// }
// if(parsion(argv, &data_config) == 1)
// {
//     write(2, "Error: invalid argument format\n", 31);
//     return 1;
// }
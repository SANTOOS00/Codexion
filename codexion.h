/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 03:32:13 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/05 16:44:15 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>

typedef enum e_scheduler
{
    FIFO,
    EDF
} t_scheduler;

typedef struct s_config
{
    int number_of_coders;      //  The number of coders and also the number of dongles.
    long time_to_burnout;        //(in milliseconds): If a coder did not start compiling within
    long time_to_compile;        // الوقت اللي كيحتاج coder باش يدير compile
    long time_to_debug;          // الوقت ديال debug
    long time_to_refactor;       // الوقت ديال refactor
    int number_of_compiles_required; // عدد المرات اللي خاص كل coder يدير compile
    long dongle_cooldown;        // الوقت اللي خاص dongle يستنى قبل ما يتستعمل مرة أخرى
    t_scheduler scheduler;       // FIFO ولا EDF
} t_config;
int parsion(int argc, char **argv, t_config *data_config);
// int ft_atoi_int(char *num_str);
// int ft_atoi_long(char *num_str);


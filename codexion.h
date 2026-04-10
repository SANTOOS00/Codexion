/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 16:12:23 by santoos           #+#    #+#             */
/*   Updated: 2026/04/09 16:38:03 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <pthread.h>
#include <stdio.h>
#include <string.h>

typedef enum e_config
{
    FIFO,
    EDF
} t_scheduler;


typedef struct s_condif{
    size_t number_of_coders;
    size_t time_to_burnout;
    size_t time_to_compile;
    size_t time_to_debug;
    size_t time_to_refactor;
    size_t number_of_compiles_required;
    size_t dongle_cooldown;
    t_scheduler scheduler;
} t_config;
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:48:31 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/13 20:20:38 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>


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


typedef struct s_malloc
{
    void *ptr;
    struct s_malloc *next;
} t_malloc;

typedef struct s_threads_id {
    pthread_t *thread_id;
} t_threads_id;


void *join_in_threads(size_t number_of_numbers, pthread_t *threads);

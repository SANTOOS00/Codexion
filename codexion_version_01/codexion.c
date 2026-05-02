/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 16:54:29 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/02 19:10:13 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"








void *coder_block_until_scheduled(void *arg)
{
    t_coder *coder;

    coder = (t_coder *)arg;

    pthread_mutex_lock(coder->mutex);
    push_queue(coder);
    coder->check_wait = false;
    // while (coder->check_wait)
    //     pthread_cond_wait(&coder->cond, coder->mutex);
    pthread_mutex_unlock(coder->mutex);
    return NULL;
}



void exit_threads(int number_coder_creates)
{
    return ;
}

t_action run_coders_threads(t_config config)
{
    t_coder **coders;
    int i;

    coders = initialize_coders(0);
    i = 0;
    while (i < config.number_of_coders)
    {
        if (pthread_create(&coders[i]->thread, NULL, coder_block_until_scheduled, coders[i]))
            return (exit_threads(i), fail);
        i++;
    }
    return success;
}



t_action start_simulation(t_config config)
{
    t_coder **coders;
    int i = 0;


    coders = initialize_coders(0);
    if (run_coders_threads(config) == fail)
        return fail;
    is_queue_full(config.number_of_coders);
    while (i < config.number_of_coders)
        pthread_join(coders[i++]->thread, NULL);
}

int main(int ac, char **av)
{
    t_config config;
    config = parse_args(ac, av);
    if (!initialize_coders(config.number_of_coders))
        return 1;
    if (!initialize_dongles(config.number_of_coders))
        return 1;
    if (!initialize_queue(config.number_of_coders))
        return 1;
    assign_dongles_to_coders(config.number_of_coders);
    if (start_simulation(config) == fail)
        return (free_source(fail, config.number_of_coders), 1);
    free_source(fail, config.number_of_coders);
    return 0;
}

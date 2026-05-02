/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_coders.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 16:54:48 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/02 18:40:43 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"




void free_coders(int i, t_coder **coders)
{
    while (i > 0)
    {
        i--;
        free(coders[i]);
    }
    free(coders);
}



t_action initialize(int number_of_coders, t_coder **coders)
{
    int i = 0;
    pthread_mutex_t *mutex;

    mutex = malloc(sizeof(pthread_mutex_t));
    if (!mutex)
        return fail;

    pthread_mutex_init(mutex, NULL);

    while (i < number_of_coders)
    {
        coders[i] = malloc(sizeof(t_coder));
        if (!coders[i])
        {
            free_coders(i, coders);
            pthread_mutex_destroy(mutex);
            free(mutex);
            return fail;
        }
        coders[i]->mutex = mutex;
        i++;
    }
    return success;
}
t_coder **initialize_coders(int number_of_coders)
{
    static t_coder **coders = NULL;

    if (coders == NULL)
    {
        coders = malloc(sizeof(t_coder *) * number_of_coders); 
        if (!coders)
            return NULL;
        if (initialize(number_of_coders, coders) == fail)
        {
            free(coders);
            coders = NULL;
            return NULL;
        }
    }
    return coders;
}
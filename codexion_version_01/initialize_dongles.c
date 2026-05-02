/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_dongles.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 16:54:51 by moerrais          #+#    #+#             */
/*   Updated: 2026/05/02 18:40:50 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_dongle *initialize_dongles(int number_of_coders)
{
    static t_dongle *dongles = NULL;
    
    if (dongles == NULL)
    {
        dongles = malloc(sizeof(t_dongle) * number_of_coders);
        if (!dongles)
            return (free_source(fail_coders, number_of_coders), NULL);
    }
    return dongles;
}
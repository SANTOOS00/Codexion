/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsion.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 19:30:09 by santoos           #+#    #+#             */
/*   Updated: 2026/03/24 19:55:58 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


int parsion(char **argv)

{
    for(int i = 1;i < 9;i++)
    {
        char *arg = argv[i];
        for(int j = 0; arg[j] != '\0'; j++)
        {
            if(!isdigit(arg[j]))
                return (1);
        }
    }
    return(0);   
}
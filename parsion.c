/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsion.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 19:30:09 by santoos           #+#    #+#             */
/*   Updated: 2026/03/23 19:39:01 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


int parsion(char **argv)
{
    for(int i = 1;i < 9;i++)
    {
        printf("s\n");
        char *arg = argv[i];
        for(int j = 0; arg[j] != '\0'; j++)
        {
            if(!isdigit(arg[j]))
                return (1);
        }
    }
    return(0);   
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsion.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 03:32:29 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/02 05:10:40 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "codexion.h"

int ft_isdigit(char c)
{
    if (c >= 48 && c <= 57)
        return 0;
    return 1;
}
int parsion(char **argv)
{
    int i = 1;
    while(i < 9)
    {
        char *arg = argv[i];
        int j = 0;
        while(arg[j] != '\0')
        {
            if(ft_isdigit(arg[j]))
                return (1);
            j++;
        }
        i++;
    }
    return(0);   
}
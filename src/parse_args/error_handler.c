/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 21:15:19 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/04 21:15:20 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../include/codexion.h"

void	error_out_of_range(const char *arg_name, const char *value)
{
	fprintf(stderr, "Error: '%s' must be between 0 and INT_MAX (got '%s').\n",
		arg_name, value);
}
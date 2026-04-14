/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/04/10 21:48:10 by username         #+#    #+#              */
/*   Updated: 2026/04/14 06:42:07 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int		parse_args(int argc, char **argv, t_config *config);
void	*create_in_threads(size_t number_of_numbers, t_threads_id *id_ths);

int	main(int argc, char **argv)
{
	t_config		config;
	t_threads_id	id_threads;

	parse_args(argc, argv, &config);
	create_in_threads(config.number_of_coders, &id_threads);
}

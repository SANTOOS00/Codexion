/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_registry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:35:36 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/16 22:20:16 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_manager_coder *get_or_create_manger_coders()
{
	static t_manager_coder *manger_coders = NULL;
	if (manger_coders == NULL)
	{
		manger_coders = malloc(sizeof(t_manager_coder));
		if (!manger_coders)
			return NULL;
		manger_coders->coders = NULL;
	}
	return manger_coders;
}

t_manager_coder *allocate_coders(int number_of_coders)
{
	t_manager_coder *manger_coders;

	manger_coders =  get_or_create_manger_coders();
	if (!manger_coders)
		return NULL;
	if (manger_coders->coders == NULL)
	{
		manger_coders->coders = malloc(sizeof(t_coder) * number_of_coders);
		if (!manger_coders->coders)
			return NULL;
	}
	return manger_coders;
}

int destroy_manger_coders(t_action action)
{
	t_manager_coder *manger_coders;

	manger_coders = get_or_create_manger_coders();
	if(!manger_coders)
		return (FREE_1);
	if (manger_coders->coders != NULL)
		free(manger_coders->coders);
	free(manger_coders);
	return (action);
}

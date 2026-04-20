/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: santoos <santoos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:48:31 by username          #+#    #+#             */
/*   Updated: 2026/04/20 14:46:57 by santoos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef struct s_condif
{
	int			number_of_coders;
	size_t		time_to_burnout;
	size_t		time_to_compile;
	size_t		time_to_debug;
	size_t		time_to_refactor;
	size_t		number_of_compiles_required;
	size_t		dongle_cooldown;
	t_scheduler	scheduler;
}	t_config;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}	t_dongle;

typedef struct s_coder
{
	int			id;
	pthread_t	thread;
	t_dongle	*left;
	t_dongle	*right;
}	t_coder;

typedef struct s_stack
{
	void			*arry_key_coders;
	struct s_stack	*next;
}	t_stack;

t_config	parse_args(int ac, char **av);

// void push(struct Node * *head_ref,
// 	int	new_data)
// {
// 	// 1. Allocate node
// 	struct Node	*new_node =
// 	(struct Node *) malloc(sizeof(struct Node));

// 	// 2. put in the data
// 	new_node->data = new_data;

// 	// 3. Make next of new node as head
// 	new_node->next = (*head_ref);

// 	// 4. move the head to point to
// 	// the new node
// 	(*head_ref) = new_node;
// }

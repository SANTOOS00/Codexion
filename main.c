/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:54:05 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/06 19:31:39 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>


int conut = 0;
pthread_mutex_t mutex;
void *test()
{
	pthread_mutex_lock(&mutex);
	int i = 0;
	while(i < 100000)
	{
		conut++;
		i++;
	}	
	pthread_mutex_unlock(&mutex);
}


int main()
{
	pthread_t t1, t2;

	pthread_create(&t1, NULL, &test, NULL);
	pthread_create(&t2, NULL, &test, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("%d", conut);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 10:18:51 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/06 10:46:05 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


// void test_task()
// {
// 	printf("test task thread\n");
// 	sleep(2);
// 	printf("ssfinich thread\n");
// 	// return NULL;
// }

// int main()
// {
// 	pthread_t t1, t2;

// 	pthread_create(&t1, NULL, &test_task, NULL);
// 	pthread_create(&t2, NULL, &test_task, NULL);
// 	pthread_join(t1, NULL);
// 	pthread_join(t2, NULL);
// }


void test_task(void *arg)
{
	char *r = (char *)arg;
	printf("%s\n", r);
	return NULL;
}


int main()
{
	void *(*ptr)(void *) = test_task;

	ptr("test pointer to function");
	test_task("test test_task");
}
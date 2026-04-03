/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 03:32:23 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/03 19:25:06 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "codexion.h"
#include <pthread.h>



void *taks1(void *arg)
{
    int i = 0;
    while(i < 5)
    {
        printf("taks 1 ==> %d\n", i);
        i++;
        sleep(2);
    }
    return NULL;
}

void *taks2(void *arg)
{
    int i = 0;
    while(i < 5)
    {
        printf("task 2 ==> %d\n", i);
        i++;
        sleep(2);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    // t_config config;
    // int i = 1;
    if(argc != 9)
    {
        write(2, "Error: invalid number of arguments\n", 35);
        return(1);
    }
    if(parsion(argv))
    {
        write(2, "Error: invalid number of arguments\n", 35);
        return(1);
    }
    // printf("not error");
    
    pthread_t t1, t2;
    pthread_t t4, t3;
    pthread_create(&t1, NULL, taks1, NULL);
    pthread_create(&t2, NULL, taks2, NULL);
    pthread_create(&t3, NULL, taks1, NULL);
    pthread_create(&t4, NULL, taks1, NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    printf("hamid ikml");
}

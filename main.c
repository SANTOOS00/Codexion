/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:21:47 by moerrais          #+#    #+#             */
/*   Updated: 2026/04/18 03:48:14 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



pthread_mutex_t mutex;
unsigned long ft_gettime_ms(void)
{
    struct timeval new;
    gettimeofday(&new, NULL);
    return ((new.tv_sec * 1000) + (new.tv_usec / 1000));
}

unsigned long ft_gettime(unsigned long time_create_coder)
{
    return (ft_gettime_ms() - time_create_coder);
}


void ft_compile(t_coder *coder, long time_ms)
{
	if(pthread_mutex_lock(&mutex) == 0)
	{
		usleep(time_ms * 1000);
		printf("%ld %d is compeling \n", ft_gettime(coder->time_create), coder->id);
		pthread_mutex_unlock(&mutex);
	}
	else{
		printf("dd");
		while(coder->active_wait)
			pthread_cond_wait(&coder->left->cond, &coder->left->mutex);
	}
}

void ft_debug(t_coder *coder)
{
	printf("%d is debugging\n", coder->id);
}

void ft_refactor(t_coder *coder)
{
	printf("%d is refactoring\n", coder->id);
}

void *rotune(void *arg)
{
	t_coder *coder;
	while(1)
	{
		coder = (t_coder *)coder;
		ft_compile(coder, coder->time_compile);
	}	
	return NULL;
}



void ft_create_threads(t_config config)
{
    t_dongle *dongle = malloc(sizeof(t_dongle) * config.number_of_coders);
    t_coder *coders = malloc(sizeof(t_coder) * config.number_of_coders);

    if (!dongle || !coders)
        return;

    for (int i = 0; i < config.number_of_coders; i++)
    {
        pthread_mutex_init(&dongle[i].mutex, NULL);
        pthread_cond_init(&dongle[i].cond, NULL);

        coders[i].id = i;
        coders[i].left = &dongle[i];
        coders[i].right = &dongle[(i + 1) % config.number_of_coders];
        coders[i].time_compile = config.time_to_compile;
        coders[i].number_compiles = config.number_of_compiles_required;
    }

    unsigned long time_start_threads = ft_gettime_ms();

    for (int i = 0; i < config.number_of_coders; i++)
    {
        coders[i].time_create = time_start_threads;
        pthread_create(&coders[i].th, NULL, rotune, &coders[i]);
    }

    for (int i = 0; i < config.number_of_coders; i++)
    {
        pthread_join(coders[i].th, NULL);
    }
}
int main(int ac, char **argv)
{
	t_config config;
	if(parse_args(ac, argv, &config))
		return (1);
	ft_create_threads(config);
}

#include "codexion.h"

static void destroy_mutex_cond_coders(t_coder **coders, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		destory_mutex_cond(&coders[i]->mutex_cond);
		i++;
	}
}



void clean_resource(t_simulation *simulation)
{
	destroy_m_c_simulation(simulation);
	clean_dongles(simulation->dongles, simulation->config.number_of_coders);
	free_2d_array((void **)simulation->dongles, simulation->config.number_of_coders);
	destroy_mutex_cond_coders(simulation->coders, simulation->config.number_of_coders);
	free_2d_array((void **)simulation->coders, simulation->config.number_of_coders);
}
#include "codexion.h"

void clean_resource(t_simulation *simulation)
{
	clean_coders(simulation->coders, simulation->config.number_of_coders);
	clean_dongles(simulation->dongles, simulation->config.number_of_coders);
	clean_mutex_cond_simulation(simulation);
}
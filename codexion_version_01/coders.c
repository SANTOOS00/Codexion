
#include"codexion.h"


t_coder **ft_allocate_coders(int number_of_coders)
{
    t_coder **coders;
    int i;

    i = 0;
    coders = (t_coder **)malloc(sizeof(t_coder *) * number_of_coders);
    if (!coders)
        return (NULL);
    while(i < number_of_coders)
    {
        coders[i] = (t_coder *)malloc (sizeof(t_coder));
        if (coders[i])
            return (ft_free_resource((void **)coders, i), false);
        i++;
    }
    return (coders);
}


void ft_free_coders(t_simulation *simulation) {
    int i;

    i = 0;
    while (i < simulation->config.number_of_coders) {
        free(simulation->coders[i]);
        i++;
    }
    free(simulation->coders);
}



void ft_clean_coders(t_simulation *simulation)
{
    int i;

    i = 0;
    while (i < simulation->config.number_of_coders)
    {
        ft_destrory_mutex_cond_var(&simulation->coders[i]->mutex_cond);
        i++;
    }
    ft_free_coders(simulation);
}



bool ft_set_coders_initial_state(t_simulation *simulation)
{
    t_coder *coder;
    int i;

    i = 0;
    while (i < simulation->config.number_of_coders)
    {
        coder = simulation->coders[i];
        coder->id = i;
        coder->status = START;
        coder->config = &simulation->config;
        coder->is_burnout = &simulation->is_burnout;
        coder->burnout_mutex = &simulation->burnout_mutex;
        coder->coders_counter_m_c = &simulation->coders_counter_m_c;
        coder->coders_counter = &simulation->coders_counter;
        coder->print_mutex = &simulation->print_mutex;
        if (!ft_init_mutex_cond_var(&coder->mutex_cond))
            return false;
    }
    return (true);
}


bool ft_init_coders(t_simulation *simulation)
{
    t_coder **coders;

    coders = ft_allocate_coders(simulation->config.number_of_coders);
    if(!coders)
        return (false);
    if(!ft_set_coders_initial_state(simulation))
    {
        ft_free_coders(simulation);
        return (false);
    }
    simulation->coders = coders;
    return (true);
}
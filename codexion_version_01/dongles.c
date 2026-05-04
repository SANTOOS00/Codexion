#include "codexion.h"

bool ft_init_dongles_initial_state(t_simulation *simulation) {
    int i;
    t_dongle **dongles;
    
    i = 0;
    dongles = simulation->dongles;
    while (i < simulation->config.number_of_coders) {
        dongles[i]->is_available = true;
        if (pthread_mutex_init(&dongles[i]->mutex, NULL)) {
            while (i > 0) {
                pthread_mutex_destroy(&dongles[i - 1]->mutex);
                i--;
            }
            return (false);
        }
        i++;
    }
    return true;
}

t_dongle **ft_allocate_dongles(int dongles_num)
{
    t_dongle **dongles;
    int i;

    i = 0;
    dongles = (t_dongle **)malloc(sizeof(t_dongle *) * dongles_num);
    if (!dongles)
        return (NULL);
    while(i < dongles_num)
    {
        dongles[i] = (t_dongle *)malloc (sizeof(t_dongle));
        if (!dongles[i])
            return (ft_free_resource((void **)dongles, i), false);
        i++;
    }
    return (dongles);
}

void ft_clean_dongles(t_simulation *simulation) {
    int i;

    i = 0;
    while (i < simulation->config.number_of_coders) {
        pthread_mutex_destroy(&simulation->dongles[i]->mutex);
        free(simulation->dongles[i]);
        i++;
    }
    free(simulation->dongles);
}

bool ft_init_dongles(t_simulation *simulation) {
    int i;
    t_dongle **dongles;
    int j;
    
    i = 0;
    j = 0;
    dongles = ft_allocate_dongles(simulation->config.number_of_coders);
    if (!dongles)
        return false;
    if (!ft_init_dongles_initial_state(simulation))
        return (ft_clean_dongles(simulation), false);
    simulation->dongles = dongles;
    return true;
}





#include "codexion.h"



static void free_coders(int number_of_dongles)
{
    t_coder **coders;
    int i;

    i = 0;
    coders = initialize_coders(0);
    while (i < number_of_dongles)
    {
        free(coders[i]->mutex);
        free(coders[i++]);
    }
    free(coders);
    return ;
}

void free_dongles(int number_of_dongles)
{
    t_dongle *dongles;
    int i;

    i = 0;
    dongles = initialize_dongles(0);

    while (i < number_of_dongles)
        pthread_mutex_destroy(&dongles[i++].mutex);
    free(dongles);
    return ;
}


void free_queue(int number_of_dongles)
{
    t_queue **queue;
    int i;

    i = 0;
    queue = initialize_queue(0);
    while(i < number_of_dongles)
    {
        free(queue[i]->mutex);
        free(queue[i++]);
    }
        
    free(queue);
    return ;
}

void free_source(t_action action ,int number_of_dongles)
{
    if (action == fail_dongles)
        free_coders(number_of_dongles);
    else if (action == fail_queue)
    {
        free_coders(number_of_dongles);
        free_dongles(number_of_dongles);
    }
    else if (action == fail)
        free_coders(number_of_dongles);
        free_dongles(number_of_dongles);
        free_queue(number_of_dongles);
    return ;   
}

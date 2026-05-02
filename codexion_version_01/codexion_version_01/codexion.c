#include "codexion.h"




void push_queue(t_coder *coder)
{
    int i;
    t_queue **queue;

    queue = initialize_queue(0); 
    return ;
}



void *coder_block_until_scheduled(void *arg)
{
    t_coder *coder;

    coder = (t_coder *)arg;
    pthread_mutex_lock(coder->mutex);
    push_queue(coder);
    // coder->check_wait = true;
    // while (coder->check_wait)
    //     pthread_cond_wait(&coder->cond, coder->mutex);
    pthread_mutex_unlock(coder->mutex);
    return NULL;
}



void exit_threads(int number_coder_creates)
{
    return ;
}

t_action run_threads(t_config config)
{
    t_coder **coders;
    int i;

    coders = initialize_coders(0);
    i = 0;
    while (i < config.number_of_coders)
    {
        if (pthread_create(&coders[i]->thread, NULL, coder_block_until_scheduled, coders[i]))
            return (exit_threads(i), fail);
        i++;
    }
    i = 0;
    // while (i < config.number_of_coders)
    //     pthread_join(coders[i++]->thread, NULL);
    return success;
}


int main(int ac, char **av)
{
    t_config config;
    config = parse_args(ac, av);
    if (!initialize_coders(config.number_of_coders))
        return 1;
    if (!initialize_dongles(config.number_of_coders))
        return 1;
    if (!initialize_queue(config.number_of_coders))
        return 1;
    assign_dongles_to_coders(config.number_of_coders);
    if (run_threads(config) == fail)
        return (free_source(fail, config.number_of_coders), 1);
    free_source(fail, config.number_of_coders);
    return 0;
}

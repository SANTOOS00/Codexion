#include "codexion.h"

void *ft_coder(void *arg) {
    t_coder *coder_state;

    coder_state = (t_coder *)arg;
    pthread_mutex_lock(&coder_state->print_mutex);
    printf("hello from coder %d\n", coder_state->id);
    pthread_mutex_unlock(&coder_state->print_mutex);
    return NULL;
}

bool ft_run_coders_threads(t_simulation *simulation) {
    int i;
    t_coder *coder;

    i = 0;
    while (i < simulation->config.number_of_coders) {
        coder = simulation->coders[i];
        pthread_create(&coder->thread, NULL, ft_coder, coder);
        i++;
    }
    return true;
}

void ft_join_coders_threads(t_simulation *simulation) {
    int i;
    t_coder *coder;

    i = 0;
    while (i < simulation->config.number_of_coders) {
        coder = simulation->coders[i];
        pthread_join(coder->thread, NULL);
        i++;
    }
}
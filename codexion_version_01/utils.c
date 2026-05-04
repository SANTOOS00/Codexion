#include "codexion.h"

bool ft_init_mutex_cond_var(t_mutex_cond *mutex_cond)
{
    if (pthread_mutex_init(&mutex_cond->mutex, NULL))
        return (false);
    if (pthread_cond_init(&mutex_cond->cond, NULL)) {
        pthread_mutex_destroy(&mutex_cond->mutex);
        return (false);
    }
    return (true);
}

void ft_destrory_mutex_cond_var(t_mutex_cond *mutex_cond) {
    pthread_mutex_destroy(&mutex_cond->mutex);
    pthread_cond_destroy(&mutex_cond->cond);
}
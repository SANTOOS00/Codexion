#include "codexion.h"

void ft_compiling_coder(t_coder *coder)
{
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    coder->status = COMPILING;
	coder->compilation_count++;
    printf("min_b3d %d is compiling\n", coder->id);
    usleep(coder->config->time_to_compile * 1000);
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void ft_debugging_coder(t_coder *coder)
{
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    coder->status = DEBUGGING;
    printf("min_b3d %d is debugging\n", coder->id);
    usleep(coder->config->time_to_debug * 1000);
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void ft_refactoring(t_coder *coder)
{
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    coder->status = REFACTORING;
    printf("min_b3d %d is refactoring\n", coder->id);
    usleep(coder->config->time_to_refactor * 1000);
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

void execute_coding_cycle(t_coder *coder)
{
	ft_compiling_coder(coder);
    return_dongles(coder);
	ft_debugging_coder(coder);
	ft_refactoring(coder);
    pthread_mutex_lock(&coder->mutex_cond.mutex);
    if (coder->compilation_count == coder->config->number_of_compiles_required)
        coder->status = FINISHED;
    pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

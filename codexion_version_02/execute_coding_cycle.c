#include "codexion.h"

void ft_compiling_coder(t_coder *coder)
{
    pthread_mutex_lock(&coder->left_dongle->m_cn_dongle.mutex);
    pthread_mutex_lock(&coder->right_dongle->m_cn_dongle.mutex);
    coder->status = COMPILING;
	coder->compilation_count++;
    printf("min_b3d %d is compiling\n", coder->id);
    usleep(coder->config->time_to_compile * 1000);
    pthread_mutex_unlock(&coder->left_dongle->m_cn_dongle.mutex);
    pthread_mutex_unlock(&coder->right_dongle->m_cn_dongle.mutex);
}

void ft_debugging_coder(t_coder *coder)
{
    coder->status = DEBUGGING;
    printf("min_b3d %d is debugging\n", coder->id);
    usleep(coder->config->time_to_debug * 1000);
}

void ft_refactoring(t_coder *coder)
{
    coder->status = REFACTORING;
    printf("min_b3d %d is refactoring\n", coder->id);
    usleep(coder->config->time_to_refactor * 1000);
}

void execute_coding_cycle(t_coder *coder)
{
	ft_compiling_coder(coder);
    return_dongles(coder);
	ft_debugging_coder(coder);
	ft_refactoring(coder);
}

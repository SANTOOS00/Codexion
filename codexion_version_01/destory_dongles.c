#include "codexion.h"


void ft_destory_dongles(t_dongle **dongles, int conut)
{
    int i;

    i = 0;
    while(i < conut)
    {
        pthread_mutex_destroy(&dongles[i]->mutex);
        pthread_cond_destroy(&dongles[i]->cond);
        i++;
    }
}
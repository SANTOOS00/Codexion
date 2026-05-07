
#include "codexion.h"

// void wait_coder(t_coder *coder)
// {
// 	pthread_mutex_lock(&coder->mutex_cond.mutex);
// 	while (coder->is_coder_waiting)
// 		pthread_cond_wait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex);	
// 	pthread_mutex_unlock(&coder->mutex_cond.mutex);
// }
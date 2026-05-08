#include "codexion.h"

void return_left_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->left_dongle->mutex);
	(coder->left_dongle->is_available) = true;
	pthread_mutex_unlock(&coder->left_dongle->mutex);
}

void return_right_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->right_dongle->mutex);
	(coder->right_dongle->is_available) = true;
	pthread_mutex_unlock(&coder->right_dongle->mutex);
}
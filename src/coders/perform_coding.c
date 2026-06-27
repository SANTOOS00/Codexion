/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_coding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:37:14 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/27 05:45:08 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static bool ft_compiling_coder(t_coder *coder);
static bool ft_debugging_coder(t_coder *coder);
static bool ft_refactoring_coder(t_coder *coder);
static bool	enqueue_coder_request(t_coder *coder);

bool    perform_coding(t_coder *coder)
{
  if (!ft_compiling_coder(coder))
    return false;
  if (!ft_debugging_coder(coder))
    return false;
  if (!ft_refactoring_coder(coder))
    return false;
  if (enqueue_coder_request(coder))
    return false;
  return true;
}

static bool	ft_compiling_coder(t_coder *coder)
{
  if (ft_is_simulation_finished(coder->is_finished_sim, coder->is_finished_sim_m))
    return (false);
  ft_print_action(coder, "is compiling");
  if (!ft_sleep_coder(coder, COMPILING))
    return false;
  return_dongles(coder);
  return true;
}

static bool	ft_debugging_coder(t_coder *coder)
{
  ft_print_action(coder, "is debugging");
  if (!ft_sleep_coder(coder, DEBUGGING))
    return false;
  return true;
}

static bool	ft_refactoring_coder(t_coder *coder)
{
  ft_print_action(coder, "is refactoring");
  if (!ft_sleep_coder(coder, REFACTORING))
    return false;
  return true;
}

static bool	enqueue_coder_request(t_coder *coder)
{
  pthread_mutex_lock(&coder->queue->mutex_queue);
  push_priority_queue(coder);
  pthread_mutex_unlock(&coder->queue->mutex_queue);

  pthread_mutex_lock(&coder->mutex_cond.mutex);
  coder->has_dongle = false;
  while (!coder->has_dongle)
    pthread_cond_wait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex);
  pthread_mutex_unlock(&coder->mutex_cond.mutex);
  if (coder->status == FINISHED)
    return (true);
  return (ft_is_simulation_finished(coder->is_finished_sim, coder->is_finished_sim_m));
}






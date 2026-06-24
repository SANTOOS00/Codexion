/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_coding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:37:14 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/24 05:08:16 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"
static bool ft_compiling_coder(t_coder *coder);
static bool ft_debugging_coder(t_coder *coder);
static bool ft_refactoring_coder(t_coder *coder);
static void ft_increment_compilation_counter(t_coder *coder);
void	update_burnout_timer(t_coder *coder);


bool    perform_coding(t_coder *coder)
{
  if (!ft_compiling_coder(coder))
    return false;
  return_dongles(coder);
  if (!ft_debugging_coder(coder))
    return false;
  if (!ft_refactoring_coder(coder))
    return false;
  return true;
}


bool ft_is_simulation_finished(bool *is_sim_finished, pthread_mutex_t *is_sim_finished_m)
{
  bool is_finished;

  is_finished = false;
  pthread_mutex_lock(is_sim_finished_m);
  if (*is_sim_finished == true)
    is_finished = true;
  pthread_mutex_unlock(is_sim_finished_m);
  return is_finished;
}



int ft_get_coder_time(t_coder *coder, t_coder_status state)
{
  if (state == COMPILING)
    return coder->config->time_to_compile;
  else if (state == DEBUGGING) 
      return coder->config->time_to_debug;
  return coder->config->time_to_refactor;    
}

bool ft_sleep_coder(t_coder *coder, int state)
{
  int     is_timed_out;
  struct   timespec	time;

  time = get_time_add_time_wait(ft_get_coder_time(coder, state));

  pthread_mutex_lock(&coder->mutex_cond.mutex);
  is_timed_out = pthread_cond_timedwait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex,
    &time);
  pthread_mutex_unlock(&coder->mutex_cond.mutex);
  return (!ft_is_simulation_finished(coder->is_finished_sim, coder->is_finished_sim_m));
}

static bool	ft_compiling_coder(t_coder *coder)
{
  if (ft_is_simulation_finished(coder->is_finished_sim, coder->is_finished_sim_m))
    return (false);
  print_coder_action(coder, "is compiling");
  if (!ft_sleep_coder(coder, COMPILING))
    return false;
  return_dongles(coder);
  return true;
}


static bool	ft_debugging_coder(t_coder *coder)
{
  print_coder_action(coder, "is debugging");
  if (!ft_sleep_coder(coder, DEBUGGING))
    return false;
  return true;
}

static bool	ft_refactoring_coder(t_coder *coder)
{
  ft_increment_compilation_counter(coder);
  print_coder_action(coder, "is refactoring");
  if (!ft_sleep_coder(coder, REFACTORING))
    return false;
  return true;
}

void	print_coder_action(t_coder *coder, char *action)
{
  long long time;

  time = get_time_start_end(coder);
  pthread_mutex_lock(coder->mutex_print);
  printf("%lld %d %s\n", time, coder->id, action);
  pthread_mutex_unlock(coder->mutex_print);
}



void	update_burnout_timer(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	coder->deadline = get_time() + coder->config->time_to_burnout;
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
}

static void ft_increment_compilation_counter(t_coder *coder)
{
  pthread_mutex_lock(&coder->mutex_cond.mutex);
	coder->compilation_count++;
  pthread_mutex_unlock(&coder->mutex_cond.mutex);
}
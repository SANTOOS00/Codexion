/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_coding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:37:14 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/18 08:22:13 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"

static bool	ft_compiling_coder(t_coder *coder);
static bool	ft_debugging_coder(t_coder *coder);
static bool	ft_refactoring_coder(t_coder *coder);
static void increment_compilation_counter(t_coder *coder);

bool	perform_coding(t_coder *coder)
{
	if (!ft_compiling_coder(coder))
    return false;
	if (!ft_debugging_coder(coder))
    return false;
	if (!ft_refactoring_coder(coder))
    return false;
  return true;
}


bool is_burnout_detected(bool *is_burnout_detected, pthread_mutex_t *is_burnout_detected_m) {
  bool is_ok;

  is_ok = true;
  pthread_mutex_lock(is_burnout_detected_m);
  if (*is_burnout_detected == true)
    is_ok = false;
  pthread_mutex_unlock(is_burnout_detected_m);
  return is_ok;
}

bool	enqueue_coder_request(t_coder *coder)
{
	pthread_mutex_lock(&coder->queue->mutex_queue);
	push_priority_queue(coder);
	pthread_mutex_unlock(&coder->queue->mutex_queue);

	pthread_mutex_lock(&coder->mutex_cond.mutex);
	coder->has_dongle = false;
	while (!coder->has_dongle)
		pthread_cond_wait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex);
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
	return (is_burnout_detected(coder->is_burnout_detected, coder->is_burnout_detected_m));
}


int ft_get_coder_time(t_coder *coder, int state) {

  if (state == 0)
    return coder->config->time_to_compile;
  else if (state == 1) 
    return coder->config->time_to_debug;
  else
      return coder->config->time_to_refactor;;
}

bool ft_sleep_coder(t_coder *coder, int state) {
  int is_timed_out;
	struct timespec	time;
  bool is_ok;

	time = get_time_add_time_wait(ft_get_coder_time(coder, state));

  is_ok = true;
	pthread_mutex_lock(&coder->mutex_cond.mutex);
	is_timed_out = pthread_cond_timedwait(&coder->mutex_cond.cond, &coder->mutex_cond.mutex,
		&time);
  if (is_timed_out != ETIMEDOUT)
    if (is_burnout_detected(coder->is_burnout_detected, coder->is_burnout_detected_m)) 
      is_ok = false;
	pthread_mutex_unlock(&coder->mutex_cond.mutex);
  if (!is_ok)
    return is_burnout_detected(coder->is_burnout_detected, coder->is_burnout_detected_m);
  return true;
}

static bool	ft_compiling_coder(t_coder *coder)
{
  bool is_ok;

  if (!enqueue_coder_request(coder))
    return false;
	print_coder_action(coder, "is compiling");
  increment_coders_counter(coder);
  if (!ft_sleep_coder(coder, 0))
    return false;
	return_dongles(coder);
  return true;
}

static bool	ft_debugging_coder(t_coder *coder)
{
	print_coder_action(coder, "is debugging");
  if (!ft_sleep_coder(coder, 2))
    return false;
  return true;
}

static bool	ft_refactoring_coder(t_coder *coder)
{
	print_coder_action(coder, "is refactoring");
  if (!ft_sleep_coder(coder, 2))
    return false;
  return true;
}

void	print_coder_action(t_coder *coder, char *action)
{
	pthread_mutex_lock(&coder->sim->mutex_print);
	printf("%lld %d %s\n", get_time_start_end(coder->sim), coder->id, action);
	pthread_mutex_unlock(&coder->sim->mutex_print);
}

static void increment_compilation_counter(t_coder *coder) {
  pthread_mutex_lock(coder->finished_coders_m);
  coder->compilation_count++;
  if (coder->compilation_count == coder->config->number_of_compiles_required) 
      coder->finished_coders_m++;
  pthread_mutex_lock(coder->finished_coders_m);
}


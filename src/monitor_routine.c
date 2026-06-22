/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerrais <moerrais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:21:10 by moerrais          #+#    #+#             */
/*   Updated: 2026/06/22 16:42:38 by moerrais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/codexion.h"
#include <pthread.h>

static void signal_coders_to_stop(t_coder **coders, int number_of_coders);
static bool is_number_of_compilation_required_completed(t_simulation *sim);

bool	wait_monitor(t_simulation *sim)
{
	pthread_mutex_lock(&sim->monitor_mu_cond.mutex);
	sim->is_watch_waiting = false;
	while (!sim->is_watch_waiting)
		pthread_cond_wait(&sim->monitor_mu_cond.cond,
			&sim->monitor_mu_cond.mutex);
	if (sim->monitor_status == ERROR_M || sim->monitor_status == FINISHED_M)
	{
		pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
		return (false);
	}
	pthread_mutex_unlock(&sim->monitor_mu_cond.mutex);
	return (true);
}

bool ft_is_burnout_detected(t_coder **coders, int number_of_coders) {
  int i;

  i = 0;
  while (i < number_of_coders) {
    if (check_coder_burnout(coders[i])) {
      print_coder_action(coders[i], "is burnout");
      return true;
    }
    i++;
  }
  return false;
}

void	detect_burnout_in_coders(t_simulation *sim)
{
	bool	ischeckboun;

  while (!ft_is_burnout_detected(sim->coders, sim->config.number_of_coders) &&
      !is_number_of_compilation_required_completed(sim))
    usleep(300);
	pthread_mutex_lock(&sim->watch_mu_cond.mutex);
	sim->watch_status = FINISHED_W;
	pthread_mutex_unlock(&sim->watch_mu_cond.mutex);
  signal_coders_to_stop(sim->coders, sim->config.number_of_coders);
}

static void signal_coders_to_stop(t_coder **coders, int number_of_coders) {
	int	i;

	i = 0;
	while (i < number_of_coders)
	{
		pthread_mutex_lock(&coders[i]->mutex_cond.mutex);
		pthread_cond_broadcast(&coders[i]->mutex_cond.cond);
		pthread_mutex_unlock(&coders[i]->mutex_cond.mutex);
		i++;
	}
}

static bool is_number_of_compilation_required_completed(t_simulation *sim) {
  bool is_finised;

  is_finised = false;
  pthread_mutex_lock(&sim->finished_coders_m);
  if (sim->finished_coders == sim->config.number_of_coders)
    is_finised = true;
  pthread_mutex_unlock(&sim->finished_coders_m);
  return (is_finised);
}

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	if (wait_monitor(sim) == false)
		return (NULL);
	detect_burnout_in_coders(sim);
	return (NULL);
}

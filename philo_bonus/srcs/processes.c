/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:02:41 by roramos           #+#    #+#             */
/*   Updated: 2023/01/14 18:36:05 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	change_semaphore_state(sem_t *forks_sem, bool increment)
{
	if (increment)
	{
		sem_wait(forks_sem);
		sem_wait(forks_sem);
		return ;
	}
	sem_post(forks_sem);
	sem_post(forks_sem);
}

void	*monitoring(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		if (get_time() - philo->time_of_last_meal 
		>= philo->props->starve_time && !philo->is_unkillable)
		{
			display_state(philo, philo->props, DEAD);
			philo->props->dead_philo = true;
			return (NULL);
		}
	}
	return (NULL);
}
void	lifespan(t_philo *philo, t_props *props, sem_t *forks_sem)
{
	pthread_t	monitoring_id;

	pthread_create(&monitoring_id, NULL, &monitoring, philo);
	pthread_detach(monitoring_id);

	while (philo->amount_of_meals != 0 && !philo->props->dead_philo)
	{
		change_semaphore_state(forks_sem, true);
		display_state(philo, props, FORK);
		display_state(philo, props, FORK);
		philo->is_unkillable = true;
		philo->amount_of_meals --;
		philo->time_of_last_meal = get_time();
		display_state(philo, props, EAT);
		msleep(props->eat_time);
		change_semaphore_state(forks_sem, false);
		display_state(philo, props, SLEEP);
		msleep(props->sleep_time);
		display_state(philo, props, THINK);
		philo->is_unkillable = false;
	}
	exit(EXIT_SUCCESS);
}

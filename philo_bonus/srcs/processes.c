/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:02:41 by roramos           #+#    #+#             */
/*   Updated: 2023/01/17 19:13:26 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitoring(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		if (is_starving(philo) && !philo->is_unkillable)
		{
			display_state(philo, DEAD);
			sem_wait(philo->props->print_sem);
			sem_post(philo->props->dead_sem);
			return (NULL);
		}
	}
	return (NULL);
}

void	lifespan(t_philo *philo)
{
	pthread_t	monitoring_id;
	
	pthread_create(&monitoring_id, NULL, &monitoring, philo);
	pthread_detach(monitoring_id);
	while (philo->amount_of_meals != 0)
	{
		pick_up_fork(philo, philo->props->forks_sem);
		eat(philo);
		put_fork_down(philo->props->forks_sem);
		sleep_and_think(philo);
	}
	exit(PHILO_ATE);
}

void	*dead_thread(void *arg)
{
	int		i;
	t_philo	*philos;

	philos = (t_philo *)arg;
	i = -1; 
	sem_wait(philos->props->dead_sem);
	sem_wait(philos->props->dead_sem);
	while (++i < philos->props->philos_amount)
		kill(philos[i].id, SIGKILL);
	return (NULL);
}

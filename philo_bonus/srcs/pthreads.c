/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:02:41 by roramos           #+#    #+#             */
/*   Updated: 2023/01/12 18:25:16 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	change_semaphore_state(sem_t forks_sem, bool increment)
{
	if (increment)
	{
		sem_wait(&forks_sem);
		sem_wait(&forks_sem);
		return ;
	}
	sem_post(&forks_sem);
	sem_post(&forks_sem);
}

void	*monitoring(t_philo *philos, t_props *props)
{
	int		i;	
	int		finish_eating;

	finish_eating = 0;
	while (finish_eating != props->philos_amount)
	{
		i = -1;
		finish_eating = 0;
		while (++i < props->philos_amount)
		{
			if ((get_time() - philos[i].time_of_last_meal)
				>= props->starve_time && !philos[i].is_unkillable)
			{
				display_state(&(philos[i]), props, DEAD);
				exit (EXIT_SUCCESS);
			}
			if (philos[i].amount_of_meals == 0)
				finish_eating ++;
		}
	}
	printf("Everyone is alive! :(\n");
	exit (EXIT_SUCCESS);
}

void	*lifespan(t_philo *philo, t_props *props, sem_t forks_sem)
{
	while (!props->dead_philo && philo->amount_of_meals != 0)
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
	return (NULL);
}

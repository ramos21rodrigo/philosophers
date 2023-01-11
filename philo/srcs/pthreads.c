/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:02:41 by roramos           #+#    #+#             */
/*   Updated: 2023/01/11 15:55:51 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	change_forks_mutex_state(t_philo *philo, bool lock)
{
	if (lock)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		return ;
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*monitoring(void *args)
{
	t_philo	*philos;
	int		i;	
	int		finish_eating;

	finish_eating = 0;
	philos = (t_philo *)args;
	while (finish_eating != philos->props->philos_amount)
	{
		i = -1;
		finish_eating = 0;
		while (++i < philos->props->philos_amount)
		{
			if ((get_time() - philos[i].time_of_last_meal)
				>= philos[i].props->starve_time && !philos[i].is_unkillable)
			{
				display_state(&(philos[i]), DEAD);
				pthread_mutex_unlock(&philos[i].print_mutex);
				return (NULL);
			}
			if (philos[i].amount_of_meals == 0)
				finish_eating ++;
		}
	}
	printf("Everyone is alive! :(\n");
	return (NULL);
}

void	*lifespan(void	*philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	while (!philo->props->dead_philo && philo->amount_of_meals != 0)
	{
		change_forks_mutex_state(philo, true);
		display_state(philo, FORK);
		display_state(philo, FORK);
		philo->is_unkillable = true;
		philo->amount_of_meals --;
		philo->time_of_last_meal = get_time();
		display_state(philo, EAT);
		msleep(philo->props->eat_time);
		change_forks_mutex_state(philo, false);
		display_state(philo, SLEEP);
		msleep(philo->props->sleep_time);
		display_state(philo, THINK);
		philo->is_unkillable = false;
	}
	return (NULL);
}

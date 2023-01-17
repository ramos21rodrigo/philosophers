/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:02:41 by roramos           #+#    #+#             */
/*   Updated: 2023/01/17 18:22:01 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*single_philo_lifespan(void	*arg)
{
	t_props		*props;

	props = (t_props *)arg;
	if (props->must_eat_times == 0)
	{
		printf("Everyone is alive! :(\n");
		return (NULL);
	}
	printf("0 1 has taken a fork\n");
	msleep(props->starve_time);
	printf("%d 1 is dead\n", props->starve_time);
	return (NULL);
}

void	*monitoring(void *args)
{
	t_philo	*philos;
	int		i;	

	philos = (t_philo *)args;
	while (philos->props->finish_eating != philos->props->philos_amount)
	{
		i = -1;
		philos->props->finish_eating = 0;
		while (++i < philos->props->philos_amount)
		{
			pthread_mutex_lock(&philos[i].can_die);
			if (is_starving(philos[i]))
			{
				display_state(&(philos[i]), DEAD);
				philos->props->dead_philo = true;
				pthread_mutex_unlock(&philos[i].print_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&philos[i].can_die);
			if (philos[i].amount_of_meals == 0)
				philos->props->finish_eating ++;
		}
	}
	return (NULL);
}

void	*lifespan(void	*philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	while (!philo->props->dead_philo && philo->amount_of_meals != 0)
	{
		pick_up_fork(philo);
		eat(philo);
		put_fork_down(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}

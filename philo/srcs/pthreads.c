/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:02:41 by roramos           #+#    #+#             */
/*   Updated: 2023/01/16 16:34:37 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
			if (is_starving(philos[i]) && !philos[i].is_unkillable)
			{
				display_state(&(philos[i]), DEAD);
				philos->props->dead_philo = true;
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
		pick_up_fork(philo);
		eat(philo);
		put_fork_down(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:47:00 by roramos           #+#    #+#             */
/*   Updated: 2023/01/17 19:05:52 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*init_philos(t_props *props)
{
	int			i;
	t_philo		*philos;

	philos = malloc(props->philos_amount * sizeof(t_philo));
	if (!philos)
		throwerror("Allocating");
	i = -1;
	while (++i < props->philos_amount)
	{
		philos[i].amount_of_meals = props->must_eat_times;
		philos[i].time_of_last_meal = get_time();
		philos[i].is_unkillable = false;
		philos[i].id = i + 1;
		philos[i].props = props;
		philos[i].is_dead = false;
	}
	return (philos);
}

void	init_semaphores(t_props *props)
{
	sem_unlink("/forks");
	sem_unlink("/dead");
	sem_unlink("/print");
	props->forks_sem = sem_open("/forks", O_CREAT, 00700 , props->philos_amount);
	props->print_sem = sem_open("/print", O_CREAT, 00700 , 1);
	props->dead_sem = sem_open("/dead", O_CREAT, 00700 , 1);
}

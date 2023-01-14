/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:47:00 by roramos           #+#    #+#             */
/*   Updated: 2023/01/14 17:19:01 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*init_philos(t_props props)
{
	int			i;
	t_philo		*philos;

	philos = malloc(props.philos_amount * sizeof(t_philo));
	if (!philos)
		throwerror("Allocating");
	i = -1;
	while (++i < props.philos_amount)
	{
		philos[i].amount_of_meals = props.must_eat_times;
		philos[i].time_of_last_meal = get_time();
		philos[i].is_unkillable = false;
		philos[i].id = i + 1;
		philos[i].props = &props;
	}
	return (philos);
}

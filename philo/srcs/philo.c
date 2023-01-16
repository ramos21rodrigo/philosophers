/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:08:40 by roramos           #+#    #+#             */
/*   Updated: 2023/01/16 16:44:54 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_philos(t_philo *philos)
{
	int			i;

	i = -1;
	while (++i < philos->props->philos_amount)
		pthread_mutex_destroy(&philos[i].mutex);
	free(philos);
}

void	start_monitoring_thread(t_philo *philos)
{
	pthread_t	monitoring_id;

	if (pthread_create(&monitoring_id, NULL, &monitoring, philos))
		throwerror_and_free("Pthread create!", philos);
	if (pthread_join(monitoring_id, NULL) != 0)
		throwerror_and_free("Pthread join!", philos);
}

void	start_philos_threads(t_philo *philos, t_props props)
{
	int			i;

	i = -1;
	philos->props->starting_time = get_time();
	while (++i < props.philos_amount)
	{
		if (pthread_create(&(philos[i].thread_id),
				NULL, &lifespan, &(philos[i])) != 0)
			throwerror_and_free("Pthread create!", philos);
	}
	start_monitoring_thread(philos);
	i = -1;
	while (++i < props.philos_amount)
	{
		if (pthread_join(philos[i].thread_id, NULL) != 0)
			throwerror_and_free("Pthread create!", philos);
	}
}

int	main(int argc, char const *argv[])
{
	t_props		props;
	t_philo		*philos;

	props = check_and_parse_arguments(argc, argv);
	philos = init_philos(props);
	start_philos_threads(philos, props);
	free_philos(philos);
	return (EXIT_SUCCESS);
}

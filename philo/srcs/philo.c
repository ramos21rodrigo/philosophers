/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:08:40 by roramos           #+#    #+#             */
/*   Updated: 2023/01/17 18:23:35 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_philos(t_philo *philos)
{
	int			i;

	i = -1;
	while (++i < philos->props->philos_amount)
	{
		pthread_mutex_destroy(&philos[i].mutex);
		pthread_mutex_destroy(&philos[i].print_mutex);
		pthread_mutex_destroy(&philos[i].can_die);
	}
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
	if (!props.dead_philo)
		printf("Everyone is alive! :(\n");
}

void	create_single_philosopher(t_props *props)
{
	pthread_t	thread_id;

	if (pthread_create(&thread_id,
			NULL, &single_philo_lifespan, props) != 0)
		throwerror("Pthread create!");
	if (pthread_join(thread_id, NULL) != 0)
		throwerror("Pthread create!");
	exit(EXIT_SUCCESS);
}

int	main(int argc, char const *argv[])
{
	t_props		props;
	t_philo		*philos;

	props = check_and_parse_arguments(argc, argv);
	if (props.philos_amount == 1)
		create_single_philosopher(&props);
	philos = init_philos(props);
	start_philos_threads(philos, props);
	free_philos(philos);
	return (EXIT_SUCCESS);
}

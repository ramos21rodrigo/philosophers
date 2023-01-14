/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:08:40 by roramos           #+#    #+#             */
/*   Updated: 2023/01/14 18:42:09 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_philos(t_philo *philos, int philos_amount)
{
	int			i;

	i = -1;
	while (++i < philos_amount)
		pthread_mutex_destroy(&philos[i].mutex);
	free(philos);
}

void	start_philos_threads(t_philo *philos, t_props props)
{
	int			i;
	pthread_t	monitoring_id;

	i = -1;
	philos->props->starting_time = get_time();
	while (++i < props.philos_amount)
	{
		if (pthread_create(&(philos[i].thread_id),
				NULL, &lifespan, &(philos[i])) != 0)
			throwerror("Pthread create!");
		if (pthread_detach(philos[i].thread_id) != 0)
			throwerror("Pthread deatch!");
	}
	if (pthread_create(&monitoring_id, NULL, &monitoring, philos))
		throwerror("Pthread create!");
	if (pthread_join(monitoring_id, NULL) != 0)
		throwerror("Pthread join!");
}

int	main(int argc, char const *argv[])
{
	t_props		props;
	t_philo		*philos;

	props = check_and_parse_arguments(argc, argv);
	philos = init_philos(props);
	start_philos_threads(philos, props);
	free_philos(philos, props.philos_amount);
	return (EXIT_SUCCESS);
}

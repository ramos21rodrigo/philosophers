/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:08:40 by roramos           #+#    #+#             */
/*   Updated: 2023/01/11 15:54:44 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	start_philos_threads(t_philo *philos, t_props props)
{
	int			i;
	pthread_t	monitoring_id;

	i = -1;
	while (++i < props.philos_amount)
	{
		philos[i].props->starting_time = get_time();
		pthread_create(&(philos[i].thread_id), NULL, &lifespan, &(philos[i]));
		pthread_detach(philos[i].thread_id);
	}
	pthread_create(&monitoring_id, NULL, &monitoring, philos);
	pthread_join(monitoring_id, NULL);
	i = -1;
	while (++i < props.philos_amount)
		pthread_mutex_destroy(&philos[i].mutex);
	free(philos);
}

int	main(int argc, char const *argv[])
{
	t_props		props;
	t_philo		*philos;

	props = check_and_parse_arguments(argc, argv);
	philos = init_philos(props);
	start_philos_threads(philos, props);
	return (EXIT_SUCCESS);
}

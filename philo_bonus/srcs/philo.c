/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:08:40 by roramos           #+#    #+#             */
/*   Updated: 2023/01/17 19:12:17 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_philos(t_philo *philos)
{
	sem_close(philos->props->forks_sem);
	sem_close(philos->props->print_sem);
	sem_close(philos->props->dead_sem);
	free(philos);
}

void	start_philos_threads(t_philo *philos)
{
	int			i;
	int			status;

	i = -1;
	philos->props->starting_time = get_time();
	while (++i < philos->props->philos_amount)
	{
		philos[i].pid = fork();
		if(philos[i].pid == 0)
			lifespan(&(philos[i]));
		usleep(1);
	}
	i = -1;
	while(++i < philos->props->philos_amount)
		waitpid(-1, &status, 0);
	printf("Everyone is alive! :(\n");
}

int	main(int argc, char const *argv[])
{
	t_props		props;
	t_philo		*philos;
	pthread_t	id;

	props = check_and_parse_arguments(argc, argv);
	philos = init_philos(&props);
	init_semaphores(&props);
	pthread_create(&id, NULL, dead_thread, philos);
	pthread_detach(id);
	start_philos_threads(philos);
	free_philos(philos);
	return (EXIT_SUCCESS);
}

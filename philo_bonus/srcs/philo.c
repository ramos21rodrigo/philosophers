/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:08:40 by roramos           #+#    #+#             */
/*   Updated: 2023/01/12 18:24:44 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	start_philos_threads(t_philo *philos, t_props *props)
{
	int			i;
	sem_t		forks_sem;
	pid_t		monitoring_id;
	int 		status;

	i = -1;
	sem_init(&forks_sem, 0, props->philos_amount);
	props->starting_time = get_time();
	while (++i < props->philos_amount)
	{
		if(fork() == 0)
			lifespan(&(philos[i]), props, forks_sem);
	}
	monitoring_id = fork();
	if(monitoring_id == 0)
			monitoring(philos, props);
	waitpid(monitoring_id, &status, WNOHANG);
	sem_destroy(&forks_sem);
	free(philos);
}

int	main(int argc, char const *argv[])
{
	t_props		props;
	t_philo		*philos;

	props = check_and_parse_arguments(argc, argv);
	philos = init_philos(props);
	start_philos_threads(philos, &props);
	return (EXIT_SUCCESS);
}

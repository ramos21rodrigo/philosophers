/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:08:40 by roramos           #+#    #+#             */
/*   Updated: 2023/01/16 19:03:48 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	start_philos_threads(t_philo *philos, t_props *props)
{
	int			i;
	int			status;
	sem_t		*forks_sem;

	i = -1;
	sem_unlink("/forks");
	sem_unlink("/print");
	forks_sem = sem_open("/forks", O_CREAT, 00700 , props->philos_amount);
	props->print_sem = sem_open("/print", O_CREAT, 00700 , 1);
	props->starting_time = get_time();
	while (++i < props->philos_amount)
	{
		philos[i].pid = fork();
		if(philos[i].pid == 0)
			lifespan(&(philos[i]), props, forks_sem);
		usleep(1);
	}
	i = -1;
	while(++i < props->philos_amount)
	{
		waitpid(-1, &status, 0);
		if(status == PHILO_ATE)
		{
			if (i == props->philos_amount - 1)
				printf("Everyone is alive! :(\n");
		}
		else if(status == PHILO_DIED)
		{
			i = -1; 
			while (++i < props->philos_amount)
				kill(philos[i].id, SIGTERM);
			return ;
		}
	}
	sem_close(forks_sem);
	sem_close(props->print_sem);
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

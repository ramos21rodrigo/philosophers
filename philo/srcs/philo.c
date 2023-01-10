/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:08:40 by roramos           #+#    #+#             */
/*   Updated: 2023/01/10 19:01:00 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*lifespan(void	*philos)
{
	t_philo *philo;

	philo = (t_philo *)philos;
	while (!philo->props->dead_philo && philo->amount_of_meals != 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		display_state(philo, FORK);
		
		philo->is_unkillable = true;
		philo->amount_of_meals --;
		philo->time_of_last_meal = get_time();
		display_state(philo, EAT);
		usleep(philo->props->eat_time * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		display_state(philo, SLEEP);
		usleep(philo->props->sleep_time * 1000);
		display_state(philo, THINK);
		philo->is_unkillable = false;
	}
	return (NULL);
}

void	*monitoring(void *args)
{
	t_philo *philos;
	int		i;	
	int		finish_eating;

	philos = (t_philo *)args;
	while(true)
	{
		i = -1;
		finish_eating = 0;
		while(++i < philos->props->philos_amount)
		{
			if ((get_time() - philos[i].time_of_last_meal) >= philos[i].props->starve_time && !philos[i].is_unkillable)
			{
				display_state(&(philos[i]), DEAD);
				pthread_mutex_unlock(&philos[i].print_mutex);
				return(NULL);
			}
			if (philos[i].amount_of_meals == 0)
				finish_eating ++;
			usleep(1 * 1000);
		}
		if (finish_eating == philos->props->philos_amount)
		{
			printf("Everyone is alive! :(\n");
			break;
		}
	}
	return(NULL);
}

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

int main(int argc, char const *argv[])
{
	t_props		props;
	t_philo		*philos;

	props = check_and_parse_arguments(argc, argv);
	philos = init_philos(props);
	start_philos_threads(philos, props);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:08:40 by roramos           #+#    #+#             */
/*   Updated: 2023/01/03 19:03:43 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*lifeline(void	*philos)
{
	t_philo *philo;

	philo = (t_philo *)philos;
	while (!philo->props->dead_philo)
	{
		printf("%u is thinking\n", philo->id + 1);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		printf("%u has taken a fork\n", philo->id + 1);
		printf("%u has taken a fork\n", philo->id + 1);

		printf("%u is eating\n", philo->id + 1);
		sleep(philo->props->eat_time);

		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		printf("%u is sleeping\n\n", philo->id + 1);
		sleep(philo->props->sleep_time);
	}
	
	return (NULL);
}

void	start_philos_threads(t_props props)
{
	unsigned int	i;
	t_philo			*philos;

	philos = malloc(props.philos_amount * sizeof(t_props));
	if(!philos)
		throwerror("Allocating");
	i = 0;
	while(i < props.philos_amount)
	{
		philos[i].id = i;
		pthread_mutex_init(&philos[i].mutex, NULL);
		philos[i].right_fork = &(philos[i].mutex);
		philos[(i + 1) % props.philos_amount].left_fork = &(philos[i].mutex);
		philos[i].props = &props;
		i++;
	}
	i = 0;
	while (i < props.philos_amount)
	{
		pthread_create(&(philos[i].thread_id), NULL, &lifeline, &(philos[i]));
		i++;
	}
	i = 0;
	while (i < props.philos_amount)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
}

int main(int argc, char const *argv[])
{
	t_props	props;	

	props = check_and_parse_arguments(argc, argv);
	start_philos_threads(props);
	pthread_exit(0);
	return 0;
}

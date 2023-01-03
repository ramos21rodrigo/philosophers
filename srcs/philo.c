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
	pthread_mutex_lock(&(philo->left_fork));

	printf("%u\n", philo->id + 1);
	
	pthread_mutex_unlock(&(philo->left_fork));
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
		pthread_mutex_init(&(philos[i].right_fork), NULL);
		philos[(i + 1) % props.philos_amount].left_fork = philos[i].right_fork;
		i++;
	}
	i = 0;
	while(i < props.philos_amount)
	{
		pthread_create(&(philos[i].thread_id), NULL, &lifeline, &philos[i]);
		i++;
	}
	i = 0;
	while(i < props.philos_amount)
	{
		pthread_detach(philos[i++].thread_id);
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

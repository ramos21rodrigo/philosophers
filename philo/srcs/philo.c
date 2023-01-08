/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:08:40 by roramos           #+#    #+#             */
/*   Updated: 2023/01/08 19:25:10 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	display_state(t_philo *philo, t_philo_state state)
{
	time_t	timer;

	timer = get_time() - philo->props->starting_time;
	if (state == THINK)
		printf("%02ld %d  is thinking\n", timer, philo->id);
	else if (state == FORK)
		printf("%02ld %d  has taken a fork\n", timer, philo->id);
	else if (state == EAT)
		printf("%02ld %d  is eating\n", timer, philo->id);
	else if (state == SLEEP)
		printf("%02ld %d  is sleeping\n", timer, philo->id);
	else if (state == DEAD)
		printf("%02ld %d is dead\n", timer, philo->id);

}

void	*hungerspan(void *philo_arg)
{
	t_philo *philo;

	philo = (t_philo *)philo_arg;
	sleep(philo->props->starve_time);
	if (philo->last_meal > get_time() - philo->props->starve_time)
	{
		display_state(philo, DEAD);
		philo->props->dead_philo = true;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	return (NULL);
}

void	*lifespan(void	*philos)
{
	t_philo *philo;

	philo = (t_philo *)philos;
	while (!philo->props->dead_philo)
	{
		pthread_create(&(philo->hunger_thread_id), NULL, &hungerspan, philo);
		pthread_detach(philo->hunger_thread_id);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		display_state(philo, FORK);
		display_state(philo, FORK);

		display_state(philo, EAT);
		philo->last_meal = get_time();
		sleep(philo->props->eat_time);

		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		display_state(philo, SLEEP);
		sleep(philo->props->sleep_time);
		display_state(philo, THINK);
	}
	return (NULL);
}

t_philo *init_philos(t_props props)
{
	int			i;
	t_philo		*philos;
	
	philos = malloc(props.philos_amount * sizeof(t_philo));
	if (!philos)
		throwerror("Allocating");
	i = -1;
	while (++i < props.philos_amount)
	{
		pthread_mutex_init(&philos[i].mutex, NULL);
		philos[i].last_meal = get_time();
		philos[i].id = i + 1;
		philos[i].right_fork = &(philos[i].mutex);
		philos[(i + 1) % props.philos_amount].left_fork = &(philos[i].mutex);
		philos[i].props = &props;
	}
	return (philos);
}

void	start_philos_threads(t_props props)
{
	int			i;
	t_philo		*philos;

	philos = init_philos(props);
	i = -1;
	while (++i < props.philos_amount)
	{
		philos[i].props->starting_time = get_time();
		pthread_create(&(philos[i].thread_id), NULL, &lifespan, &(philos[i]));
	}
	i = -1;
	while (++i < props.philos_amount)
	{
		pthread_join(philos[i].thread_id, NULL);
		pthread_mutex_destroy(&philos[i].mutex);
	}
}

int main(int argc, char const *argv[])
{
	t_props	props;	

	props = check_and_parse_arguments(argc, argv);
	start_philos_threads(props);
	pthread_exit(0);
	return (EXIT_SUCCESS);
}

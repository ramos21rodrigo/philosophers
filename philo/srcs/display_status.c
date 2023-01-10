/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:01:02 by roramos           #+#    #+#             */
/*   Updated: 2023/01/10 19:05:29 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	display_state(t_philo *philo, t_philo_state state)
{
	time_t	timer;

	timer = get_time() - philo->props->starting_time;
	pthread_mutex_lock(&philo->print_mutex);
	if (state == THINK)
		printf("%ld %d  is thinking\n", timer, philo->id);
	else if (state == FORK)
	{
		printf("%ld %d  has taken a fork\n", timer, philo->id);
		printf("%ld %d  has taken a fork\n", timer, philo->id);
	}
	else if (state == EAT)
		printf("%ld %d  is eating\n", timer, philo->id);
	else if (state == SLEEP)
		printf("%ld %d  is sleeping\n", timer, philo->id);
	else if (state == DEAD)
		printf("%ld %d is dead\n", timer, philo->id);
	pthread_mutex_unlock(&philo->print_mutex);
}
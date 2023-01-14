/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:08:26 by roramos           #+#    #+#             */
/*   Updated: 2023/01/14 18:42:19 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	change_forks_mutex_state(t_philo *philo, bool lock)
{
	if (lock)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		return ;
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat(t_philo	*philo)
{
	philo->is_unkillable = true;
	philo->amount_of_meals --;
	philo->time_of_last_meal = get_time();
	display_state(philo, EAT);
	msleep(philo->props->eat_time);
}

void	sleep_and_think(t_philo	*philo)
{
	display_state(philo, SLEEP);
	msleep(philo->props->sleep_time);
	display_state(philo, THINK);
	philo->is_unkillable = false;
}

void	pick_up_fork(t_philo	*philo)
{
	change_forks_mutex_state(philo, true);
	display_state(philo, FORK);
	display_state(philo, FORK);
}

void	put_fork_down(t_philo	*philo)
{
	change_forks_mutex_state(philo, false);
}

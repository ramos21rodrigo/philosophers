/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:04:06 by roramos           #+#    #+#             */
/*   Updated: 2023/01/17 19:12:45 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	change_semaphore_state(sem_t *forks_sem, bool increment)
{
	if (increment)
	{
		sem_wait(forks_sem);
		sem_wait(forks_sem);
		return ;
	}
	sem_post(forks_sem);
	sem_post(forks_sem);
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

void	pick_up_fork(t_philo *philo, sem_t *forks_sem)
{
	change_semaphore_state(forks_sem, true);
	display_state(philo, FORK);
	display_state(philo, FORK);
}

void	put_fork_down(sem_t *forks_sem)
{
	change_semaphore_state(forks_sem, false);
}

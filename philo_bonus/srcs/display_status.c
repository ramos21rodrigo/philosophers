/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:01:02 by roramos           #+#    #+#             */
/*   Updated: 2023/01/17 16:04:00 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


static inline char	*get_state(t_philo_state state)
{
	if (state == THINK)
		return ("is thinking\n");
	if (state == FORK)
		return ("has taken a fork\n");
	if (state == EAT)
		return ("is eating\n");
	if (state == SLEEP)
		return ("is sleeping\n");
	return ("is dead\n");
}

void	display_state(t_philo *philo, t_philo_state state)
{
	time_t	timer;

	sem_wait(philo->props->print_sem);
	timer = get_time() - philo->props->starting_time;
	printf("%ld %d %s", timer, philo->id, get_state(state));
	sem_post(philo->props->print_sem);
}

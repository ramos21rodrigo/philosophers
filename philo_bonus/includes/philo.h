/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:12:19 by roramos           #+#    #+#             */
/*   Updated: 2023/01/12 18:25:25 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/wait.h>

typedef struct s_props
{
	time_t			starting_time;
	bool			dead_philo;
	int				philos_amount;
	int				must_eat_times;
	int				starve_time;
	int				eat_time;
	int				sleep_time;
}				t_props;

typedef struct s_philo
{
	int				id;
	time_t			time_of_last_meal;
	int				amount_of_meals;
	bool			is_unkillable;
}				t_philo;

typedef enum e_philo_state{
	DEAD,
	THINK,
	FORK,
	EAT,
	SLEEP
}	t_philo_state;

/* Throw error on call */
void	throwerror(char *error);

/* Get current time */
time_t	get_time(void);

/* Verify arguments */
t_props	check_and_parse_arguments(int argc, char const *argv[]);

/* Init philosophers*/
t_philo	*init_philos(t_props props);

/* Suspend execution for miliseconds intervals */
void	msleep(int time);

/* Display philospher state*/
void	display_state(t_philo *philo, t_props *props, t_philo_state state);

/* Lock or unlock mutex */
void	change_forks_mutex_state(t_philo *philo, bool lock);

/*  Monotoring any dead philo or 0 meals left*/
void	*monitoring(t_philo *philos, t_props *props);

/* Philosopher life */
void	*lifespan(t_philo *philo, t_props *props, sem_t forks_sem);

#endif
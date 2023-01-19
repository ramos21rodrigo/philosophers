/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:12:19 by roramos           #+#    #+#             */
/*   Updated: 2023/01/19 17:00:16 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_props
{
	time_t			starting_time;
	bool			dead_philo;
	int				philos_amount;
	int				must_eat_times;
	int				starve_time;
	int				eat_time;
	int				sleep_time;
	int				finish_eating;
}				t_props;

typedef struct s_philo
{
	t_props			*props;
	pthread_t		thread_id;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	mutex;
	pthread_mutex_t	can_die;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	time_t			time_of_last_meal;
	int				id;
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

/* Get current time */
time_t	get_time(void);

/* Verify arguments */
t_props	check_and_parse_arguments(int argc, char const *argv[],
			bool *should_exit);

/* Init philosophers*/
t_philo	*init_philos(t_props props);

/* Suspend execution for miliseconds intervals */
void	msleep(int time);

/* Display philospher state*/
void	display_state(t_philo *philo, t_philo_state state);

/* Lock or unlock mutex */
void	change_forks_mutex_state(t_philo *philo, bool lock);

/*  Monotoring any dead philo or 0 meals left*/
void	*monitoring(void *args);

/* Philosopher life */
void	*lifespan(void	*philos);
void	*single_philo_lifespan(void	*arg);

/* Free philos and mutexes */
void	free_philos(t_philo *philos);

/* Philosophers actions */
void	eat(t_philo	*philo);
void	sleep_and_think(t_philo	*philo);
void	pick_up_fork(t_philo *philo);
void	put_fork_down(t_philo *philo);

static inline bool	is_starving(t_philo	philo)
{
	return (get_time() - philo.time_of_last_meal
		>= philo.props->starve_time);
}

#endif
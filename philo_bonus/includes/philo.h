/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:12:19 by roramos           #+#    #+#             */
/*   Updated: 2023/01/17 19:12:57 by roramos          ###   ########.fr       */
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
# include <fcntl.h>
# include <signal.h>
# include <pthread.h>

# define PHILO_DIED 1
# define PHILO_ATE 0

typedef struct s_props
{
	sem_t			*print_sem;
	sem_t			*forks_sem;
	sem_t			*dead_sem;
	time_t			starting_time;
	int				philos_amount;
	int				must_eat_times;
	int				starve_time;
	int				eat_time;
	int				sleep_time;
}				t_props;

typedef struct s_philo
{
	sem_t			*can_die;
	t_props			*props;
	int				id;
	time_t			time_of_last_meal;
	int				pid;
	int				amount_of_meals;
	bool			is_dead;
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
t_philo	*init_philos(t_props *props);

/* Init semaphores */
void	init_semaphores(t_props *props);

/* Suspend execution for miliseconds intervals */
void	msleep(int time);

/* Display philospher state*/
void	display_state(t_philo *philo, t_philo_state state);

/* Lock or unlock semaphore */
void	change_semaphore_state(sem_t *forks_sem, bool increment);

/*  Monotoring any dead philo or 0 meals left*/
void	*monitoring(void *arg);

/* Philosopher life */
void	lifespan(t_philo *philo);

void	*dead_thread(void *arg);

/* Philosophers actions */
void	eat(t_philo	*philo);
void	sleep_and_think(t_philo	*philo);
void	pick_up_fork(t_philo *philo, sem_t *forks_sem);
void	put_fork_down(sem_t *forks_sem);

static inline bool	is_starving(t_philo	*philo)
{
	return (get_time() - philo->time_of_last_meal
		>= philo->props->starve_time);
}


#endif
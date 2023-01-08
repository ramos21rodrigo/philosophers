/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:12:19 by roramos           #+#    #+#             */
/*   Updated: 2023/01/08 19:15:32 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
#  define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

typedef	struct s_props
{
	bool 			dead_philo;
	int				philos_amount;
	int				must_eat_times;
	int				starve_time;
	int				eat_time;
	int				sleep_time;
	time_t			starting_time;
}				t_props;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	pthread_t		hunger_thread_id;
	pthread_mutex_t	mutex;
	pthread_mutex_t *left_fork;
	pthread_mutex_t	*right_fork;
	time_t			last_meal;
	t_props 		*props;
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
time_t	get_time();

/* Verify arguments */
t_props	check_and_parse_arguments(int argc, char const *argv[]);

# endif
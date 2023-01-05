/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:12:19 by roramos           #+#    #+#             */
/*   Updated: 2023/01/05 16:38:13 by roramos          ###   ########.fr       */
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
	int				philos_amount;
	int				idle_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat_times;
	bool 			dead_philo;
	struct timeval	starting_time;
}				t_props;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	pthread_mutex_t	mutex;
	pthread_mutex_t *left_fork;
	pthread_mutex_t	*right_fork;
	t_props 		*props;
}				t_philo;

typedef enum e_philo_state{
	DEAD,
	THINK,
	FORK,
	EAT,
	SLEEP
}	t_philo_state;

//Throw error on call
void	throwerror(char *error);

// Verify arguments
t_props	check_and_parse_arguments(int argc, char const *argv[]);

# endif
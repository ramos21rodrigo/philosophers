/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:12:19 by roramos           #+#    #+#             */
/*   Updated: 2023/01/03 18:19:51 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
#  define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <unistd.h>

typedef	struct s_props
{
	unsigned int	philos_amount;
	unsigned int	idle_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	int				must_eat_times;
}				t_props;

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		thread_id;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
}				t_philo;


inline	t_philo	init_philo()
{
	return(t_philo){
		.thread_id = 0
	};
}

//Throw error on call
void	throwerror(char *error);

// Verify arguments
t_props	check_and_parse_arguments(int argc, char const *argv[]);

# endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throwerror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:13:43 by roramos           #+#    #+#             */
/*   Updated: 2023/01/17 14:43:50 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	throwerror(char *error)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, "\n", 2);
	exit(EXIT_FAILURE);
}

void	throwerror_and_free(char *error, t_philo *philos)
{
	free_philos(philos);
	throwerror(error);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throwerror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:13:43 by roramos           #+#    #+#             */
/*   Updated: 2023/01/16 16:44:44 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	throwerror(char *error)
{
	printf("Error: %s\n", error);
	exit(EXIT_FAILURE);
}

void	throwerror_and_free(char *error, t_philo *philos)
{
	free_philos(philos);
	throwerror(error);
}

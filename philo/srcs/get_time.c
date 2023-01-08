/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:41:54 by roramos           #+#    #+#             */
/*   Updated: 2023/01/08 19:12:38 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	get_time()
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return(current_time.tv_sec / 1000);
}
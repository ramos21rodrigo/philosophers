/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:11:34 by roramos           #+#    #+#             */
/*   Updated: 2023/01/16 18:45:17 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_latoi(const char *str)
{
	long	i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] && (str[i] == '\f' || str[i] == '\t' || str[i] == ' '
			|| str[i] == '\n' || str[i] == '\r' || str[i] == '\v'))
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i++] == '-')
		sign = -1;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + str[i++] - '0';
	return (result * sign);
}

unsigned int	check_int(const char *arg)
{
	long	n_arg;

	n_arg = ft_latoi(arg);
	if (!n_arg && *arg != '0')
		throwerror("All arguments must be numbers!");
	if (n_arg <= 0)
		throwerror("All arguments must be positive!");
	if ((n_arg <= INT_MIN) || (n_arg >= INT_MAX))
		throwerror("All arguments must be ints!");
	return ((unsigned int)n_arg);
}

t_props	check_and_parse_arguments(int argc, char const *argv[])
{
	t_props	props;

	if (argc != 5 && argc != 6)
		throwerror("Invalid number of arguments!");
	props.philos_amount = check_int(argv[1]);
	props.starve_time = check_int(argv[2]);
	props.eat_time = check_int(argv[3]);
	props.sleep_time = check_int(argv[4]);
	if (argc == 6)
		props.must_eat_times = check_int(argv[5]);
	else
		props.must_eat_times = -1;
	return (props);
}

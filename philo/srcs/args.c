/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:11:34 by roramos           #+#    #+#             */
/*   Updated: 2023/01/19 16:59:26 by roramos          ###   ########.fr       */
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

unsigned int	check_int(const char *arg, bool *should_exit)
{
	long	n_arg;

	n_arg = ft_latoi(arg);
	if (!n_arg && *arg != '0')
	{
		printf("All arguments must be numbers!\n");
		*should_exit = true;
		return (1);
	}
	if (n_arg <= 0)
	{
		printf("All arguments must be positive!\n");
		*should_exit = true;
		return (1);
	}
	if ((n_arg <= INT_MIN) || (n_arg >= INT_MAX))
	{
		printf("All arguments must be ints!\n");
		*should_exit = true;
		return (1);
	}
	return ((unsigned int)n_arg);
}

t_props	check_and_parse_arguments(int argc, char const *argv[],
	bool *should_exit)
{
	t_props	props;

	if (argc != 5 && argc != 6)
	{
		printf("Invalid number of arguments!\n");
		*should_exit = true;
	}
	props.philos_amount = check_int(argv[1], should_exit);
	props.starve_time = check_int(argv[2], should_exit);
	props.eat_time = check_int(argv[3], should_exit);
	props.sleep_time = check_int(argv[4], should_exit);
	if (argc == 6 && argv[5][0] == '0' && argv[5][1] == '\0')
		props.must_eat_times = 0;
	else if (argc == 6)
		props.must_eat_times = check_int(argv[5], should_exit);
	else
		props.must_eat_times = -1;
	props.dead_philo = false;
	props.finish_eating = 0;
	return (props);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:44:33 by dberes            #+#    #+#             */
/*   Updated: 2024/04/16 13:44:42 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_timestamp(void)
{
	long long		timestamp_1;
	long long		timestamp_2;
	long long		timestamp;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	timestamp_1 = tv.tv_usec / 1000;
	timestamp_2 = tv.tv_sec * 1000;
	timestamp = timestamp_2 + timestamp_1;
	return (timestamp);
}

int	get_rel_time(long long start_time)
{
	int	rel_timestamp;

	rel_timestamp = get_timestamp() - start_time;
	return (rel_timestamp);
}

int	philo_atoi(char	*str)
{
	int	result;
	int	digit;
	int	i;

	i = 0;
	result = 0;
	while (str[i])
	{
		digit = str[i] - 48;
		result = result * 10 + digit;
		i++;
	}
	return (result);
}

int	check_non_num(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] < 48 || value[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

int	check_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong input\n");
		return (1);
	}
	i = 0;
	while (i < argc - 1)
	{
		if (philo_atoi(argv[i + 1]) < 1 || check_non_num(argv[i + 1]))
		{
			printf("Wrong input\n");
			return (1);
		}
		i++;
	}
	return (0);
}

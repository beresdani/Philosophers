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

void	put_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

/*
void print_fork_array(t_args *args)
{
	int i;

	i = 0;
	while (i < args->num_phil)
	{
		printf("%d\n", args->fork_array[i]);
		i++;
	}
}*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:46:07 by dberes            #+#    #+#             */
/*   Updated: 2024/04/16 13:46:27 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	try_to_eat_last(t_args *args, int index)
{
	pthread_mutex_lock(&args->fork_array[index - 1]);
	pthread_mutex_lock(&args->fork_array[0]);
	pthread_mutex_lock(&args->mutex);
	printf("%lld %d has taken a fork\n", get_timestamp(), index);
	printf("%lld %d has taken a fork\n", get_timestamp(), index);
	printf("%lld %d is eating\n", get_timestamp(), index);
	pthread_mutex_unlock(&args->mutex);
	args->last_fed = get_timestamp();
	usleep(args->time_eat * 1000);
	pthread_mutex_unlock(&args->fork_array[0]);
	pthread_mutex_unlock(&args->fork_array[index - 1]);
	return (0);
}

int	try_to_eat(t_args *args, int index)
{
	pthread_mutex_lock(&args->fork_array[index - 1]);
	pthread_mutex_lock(&args->fork_array[index]);
	pthread_mutex_lock(&args->mutex);
	printf("%lld %d has taken a fork\n", get_timestamp(), index);
	printf("%lld %d has taken a fork\n", get_timestamp(), index);
	printf("%lld %d is eating\n", get_timestamp(), index);
	pthread_mutex_unlock(&args->mutex);
	args->last_fed = get_timestamp();
	usleep(args->time_eat * 1000);
	pthread_mutex_unlock(&args->fork_array[index]);
	pthread_mutex_unlock(&args->fork_array[index - 1]);
	return (0);
}

int	last_phil_loop(t_args *args, int index)
{
	int	num_eats;

	num_eats = 0;
	while (1)
	{
		sleep_cycle(args, index);
		if (check_death(args, index) || args->death)
			return (1);
		think_cycle(args, index);
		if (check_death(args, index) || args->death)
			return (1);
		if (args->num_phil != 1)
			try_to_eat_last(args, index);
		if (check_death(args, index) || args->death)
			return (1);
		if (check_end(args, num_eats))
			return (1);
		num_eats++;
	}
	/*
	if (!args->fork_array[0])
	{
		args->fork_array[0] = 1;
		printf("%lld Phil %d has taken a fork\n", get_timestamp(), index);
		printf("%lld Phil %d is eating\n", get_timestamp(), index);
		args->last_fed = get_timestamp();
		usleep(args->time_eat * 1000);
	}
	pthread_mutex_unlock(&args->mutex);*/
}

int	even_loop(t_args *args, int index)
{
	int	num_eats;

	num_eats = 0;
	while (1)
	{
		if (check_death(args, index) || args->death)
			return (1);
		//change printf with putstr
		printf("%lld %d is thinking\n", get_timestamp(), index);
		//usleep(args->time_eat *1000);
		try_to_eat(args, index);
		if (check_end(args, num_eats))
			return (1);
		if (check_death(args, index) || args->death)
			return (1);
		sleep_cycle(args, index);
		if (check_death(args, index) || args->death)
			return (1);
		num_eats++;
	}
}

int	odd_loop(t_args *args, int index)
{
	int	num_eats;

	num_eats = 0;
	while (1)
	{	
		try_to_eat(args, index);
		if (check_death(args, index) || args->death)
			return (1);
		if (check_end(args, num_eats))
			return (1);
		sleep_cycle(args, index);
		if (check_death(args, index) || args->death)
			return (1);
		think_cycle(args, index);
		if (check_death(args, index) || args->death)
			return (1);
		num_eats++;
	}
}
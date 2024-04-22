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

int	try_to_eat(t_args *args, int index)
{
	int	fork1;

	fork1 = 0;
	pthread_mutex_lock(&args->mutex);
	/*if (args->fork_array[index - 1])
		printf("Phil %d Fork taken\n", index);*/
	if (!args->fork_array[index - 1])
	{
		args->fork_array[index - 1] = 1;
		fork1 = 1;
	}
	pthread_mutex_unlock(&args->mutex);

	//fork 2 + eating
	pthread_mutex_lock(&args->mutex);
	if (fork1 && index == args->num_phil && !args->fork_array[0])
	{
		args->fork_array[0] = 1;
		printf("%lld Phil %d has taken a fork\n", get_timestamp(), index);
		printf("%lld Phil %d has taken a fork\n", get_timestamp(), index);
		printf("%lld Phil %d is eating\n", get_timestamp(), index);
		args->last_fed = get_timestamp();
		usleep(args->time_eat * 1000);
		pthread_mutex_unlock(&args->mutex);
		stop_eating(args, index);
		return (1);
	}
	else if (fork1 && !args->fork_array[index])
	{
		args->fork_array[index] = 1;
		printf("%lld Phil %d has taken a fork\n", get_timestamp(), index);
		printf("%lld Phil %d has taken a fork\n", get_timestamp(), index);
		printf("%lld Phil %d is eating\n", get_timestamp(), index);
		args->last_fed = get_timestamp();
		usleep(args->time_eat * 1000);
		pthread_mutex_unlock(&args->mutex);
		stop_eating(args, index);
		return (1);
	}
	args->fork_array[index - 1] = 0;
	pthread_mutex_unlock(&args->mutex);
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
		while (1)
		{
			if (check_death(args, index) || args->death)
				return (1);
			if (try_to_eat(args, index) == 1)
				break ;
		}
		if (check_death(args, index) || args->death)
			return (1);
		if (args->is_end && num_eats == args->num_rounds - 1)
		{
			args->ended = 1;
			return (0);
		}
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
		printf("%lld Phil %d is thinking\n", get_timestamp(), index);
		usleep(args->time_eat * 1000);
		while (1)
		{
			if (check_death(args, index) || args->death)
				return (1);
			if (try_to_eat(args, index) == 1)
				break ;
		}
		if (args->is_end && num_eats == args->num_rounds - 1)
		{
			args->ended = 1;
			return (0);
		}
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
		while (1)
		{
			if (check_death(args, index) || args->death)
				return (1);
			if (try_to_eat(args, index) == 1)
				break ;
		}
		if (check_death(args, index) || args->death)
			return (1);
		if (args->is_end && num_eats == args->num_rounds - 1)
		{
			args->ended = 1;
			return (0);
		}
		sleep_cycle(args, index);
		if (check_death(args, index) || args->death)
			return (1);
		think_cycle(args, index);
		if (check_death(args, index) || args->death)
			return (1);
		num_eats++;
	}
}
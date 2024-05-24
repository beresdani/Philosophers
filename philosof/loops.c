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
	pthread_mutex_lock(&args->fork_array[0]);
	if (args->common_data->death == 1 || check_death(args, index))
	{
		pthread_mutex_unlock(&args->fork_array[0]);
		return (1);
	}
	pthread_mutex_lock(&args->fork_array[index - 1]);	
	pthread_mutex_lock(&args->common_data->print_mutex);
	printf("%d %d has taken a fork\n", get_rel_time(args->common_data->start_time), index);
	printf("%d %d has taken a fork\n", get_rel_time(args->common_data->start_time), index);
	printf("%d %d is eating\n", get_rel_time(args->common_data->start_time), index);
	args->last_fed = get_rel_time(args->common_data->start_time);
	pthread_mutex_unlock(&args->common_data->print_mutex);
	if (time_till_death(args) < args->time_eat)
		usleep(time_till_death(args) * 1000);
	else
	if (ft_usleep_eat(args, index))
	{
		if (index == args->num_phil)
			pthread_mutex_unlock(&args->fork_array[0]);
		else 
			pthread_mutex_unlock(&args->fork_array[index]);
		pthread_mutex_unlock(&args->fork_array[index - 1]);
		return (1);
	}
	pthread_mutex_unlock(&args->fork_array[index - 1]);
	pthread_mutex_unlock(&args->fork_array[0]);
	return (0);
}

int	try_to_eat(t_args *args, int index)
{
	pthread_mutex_lock(&args->fork_array[index - 1]);
	/*if (args->common_data->death == 1 || check_death(args, index))
	{
		pthread_mutex_unlock(&args->fork_array[index - 1]);
		return (1);
	}*/
	if (index == args->num_phil)
		pthread_mutex_lock(&args->fork_array[0]);
	else 
		pthread_mutex_lock(&args->fork_array[index]);
	pthread_mutex_lock(&args->common_data->print_mutex);
	printf("%d %d has taken a fork\n", get_rel_time(args->common_data->start_time), index);
	printf("%d %d has taken a fork\n", get_rel_time(args->common_data->start_time), index);
	printf("%d %d is eating\n", get_rel_time(args->common_data->start_time), index);
	args->last_fed = get_rel_time(args->common_data->start_time);
	pthread_mutex_unlock(&args->common_data->print_mutex);
	if (ft_usleep_eat(args, index))
	{
		if (index == args->num_phil)
			pthread_mutex_unlock(&args->fork_array[0]);
		else 
			pthread_mutex_unlock(&args->fork_array[index]);
		pthread_mutex_unlock(&args->fork_array[index - 1]);
		return (1);
	}
	if (index == args->num_phil)
		pthread_mutex_unlock(&args->fork_array[0]);
	else 
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
		/*if (check_death(args, index) || args->common_data->death)
			return (1);*/
		pthread_mutex_lock(&args->common_data->print_mutex);
		printf("%d %d is thinking\n", get_rel_time(args->common_data->start_time), index);
		pthread_mutex_unlock(&args->common_data->print_mutex);
		usleep(args->time_eat * 10);
		/*if (check_death(args, index) || args->common_data->death)
			return (1);*/
		usleep(50);
		if (args->num_phil != 1)
			if (try_to_eat_last(args, index))
				return (1);
		if (check_end(args, num_eats))
			return (1);
		/*if (check_death(args, index) || args->common_data->death)
			return (1);*/
		num_eats++;
	}
}

int	even_loop(t_args *args, int index)
{
	int	num_eats;
	int	death_value;

	num_eats = 0;
	while (1)
	{
		/*if (check_death(args, index) || args->common_data->death)
			return (1);
		usleep(50);*/
		pthread_mutex_lock(&args->common_data->print_mutex);
		printf("%d %d is thinking\n", get_rel_time(args->common_data->start_time), index);
		pthread_mutex_unlock(&args->common_data->print_mutex);
		usleep(50);
		pthread_mutex_lock(&args->common_data->deadphil_mutex);
		death_value = args->common_data->death;
		pthread_mutex_unlock(&args->common_data->deadphil_mutex);
		if (death_value == 1 || check_death(args, index))
			return (1);
		if (try_to_eat(args, index))
			return (1);
		if (check_end(args, num_eats))
			return (1);
		/*if (check_death(args, index) || args->common_data->death)
			return (1);*/
		sleep_cycle(args, index);
		/*if (check_death(args, index) || args->common_data->death)
			return (1);*/
		num_eats++;
	}
}

int	odd_loop(t_args *args, int index)
{
	int	num_eats;

	num_eats = 0;
	while (1)
	{
		if (try_to_eat(args, index))
			return (1);
		/*if (check_death(args, index) || args->common_data->death)
			return (1);*/
		if (check_end(args, num_eats))
			return (1);
		sleep_cycle(args, index);
		/*if (check_death(args, index) || args->common_data->death)
			return (1);*/
		pthread_mutex_lock(&args->common_data->print_mutex);
		printf("%d %d is thinking\n", get_rel_time(args->common_data->start_time), index);
		pthread_mutex_unlock(&args->common_data->print_mutex);
		usleep(50);
		/*if (check_death(args, index) || args->common_data->death)
			return (1);*/
		num_eats++;
	}
}

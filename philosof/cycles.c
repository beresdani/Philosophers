/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:49:02 by dberes            #+#    #+#             */
/*   Updated: 2024/04/16 13:49:04 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_till_death(t_args *args)
{
	int	since_fed;

	since_fed = get_rel_time(args->start_time) - args->last_fed;
	if (since_fed < args->time_to_die)
		return (args->time_to_die - since_fed);
	else
		return (0);
}

int	sleep_cycle(t_args *args, int index)
{
	pthread_mutex_lock(&args->common_data->print_mutex);
	printf("%d %d is sleeping\n", get_rel_time(args->start_time), index);
	pthread_mutex_unlock(&args->common_data->print_mutex);
	if (ft_usleep_sleep(args, index))
	{
		return (1);
	}
	return (0);
}

int	think_cycle(t_args *args, int index)
{
	pthread_mutex_lock(&args->common_data->deadphil_mutex);
	if (args->common_data->death == 0)
	{
		pthread_mutex_unlock(&args->common_data->deadphil_mutex);
		pthread_mutex_lock(&args->common_data->print_mutex);
		printf("%d %d is thinking\n",
			get_rel_time(args->start_time), index);
		pthread_mutex_unlock(&args->common_data->print_mutex);
		if (args->time_sleep < args->time_eat)
			usleep((args->time_eat - args->time_sleep) * 1000 + 2000);
		else
			usleep(2000);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&args->common_data->deadphil_mutex);
		return (1);
	}
}

void	eat_printer(t_args *args, int index)
{
	pthread_mutex_lock(&args->common_data->print_mutex);
	printf("%d %d has taken a fork\n", get_rel_time(args->start_time), index);
	printf("%d %d has taken a fork\n", get_rel_time(args->start_time), index);
	printf("%d %d is eating\n", get_rel_time(args->start_time), index);
	pthread_mutex_unlock(&args->common_data->print_mutex);
	pthread_mutex_lock(&args->mutex);
	args->last_fed = get_rel_time(args->start_time);
	pthread_mutex_unlock(&args->mutex);
}

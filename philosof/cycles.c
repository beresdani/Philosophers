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

int	check_death(t_args *args, int index)
{
	int	dead_philo;

	pthread_mutex_lock(&args->mutex);
	dead_philo = args->common_data->dead_philo;
	pthread_mutex_unlock(&args->mutex);
	if ((get_timestamp(args) - args->last_fed) >= args->time_to_die)
	{
		pthread_mutex_lock(&args->mutex);
		args->death = 1;
		pthread_mutex_unlock(&args->mutex);
		if (dead_philo == -1)
		{
			pthread_mutex_lock(&args->mutex);
			args->common_data->dead_philo = index;
			pthread_mutex_unlock(&args->mutex);
		}
		return (1);
	}
	return (0);
}

int	time_till_death(t_args *args)
{
	int	since_fed;

	since_fed = get_timestamp(args) - args->last_fed;
	if (since_fed < args->time_to_die)
		return (args->time_to_die - since_fed);
	else
		return (0);
}

void	sleep_cycle(t_args *args, int index)
{
	pthread_mutex_lock(&args->print_mutex);
	printf("%lld %d is sleeping\n", get_timestamp(args), index);
	pthread_mutex_unlock(&args->print_mutex);
	if (time_till_death(args) < args->time_sleep)
	{
		usleep(time_till_death(args) * 1000);
		return ;
	}
	usleep(args->time_sleep * 1000);
}

void	think_cycle(t_args *args, int index)
{
	pthread_mutex_lock(&args->mutex);
	printf("%lld %d is thinking\n", get_timestamp(args), index);
	pthread_mutex_unlock(&args->mutex);
	usleep(args->time_sleep * 1000);
}

int	check_end(t_args *args, int num_eats)
{
	int	is_end;
	int num_rounds;

	pthread_mutex_lock(&args->mutex);
	is_end = args->is_end;
	pthread_mutex_unlock(&args->mutex);
	pthread_mutex_lock(&args->mutex);
	num_rounds = args->num_rounds;
	pthread_mutex_unlock(&args->mutex);
	if (is_end && num_eats == num_rounds - 1)
	{
		pthread_mutex_lock(&args->mutex);
		args->ended = 1;
		pthread_mutex_unlock(&args->mutex);
		return (1);
	}
	return (0);
}

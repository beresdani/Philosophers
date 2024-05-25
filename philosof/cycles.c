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

void	sleep_cycle(t_args *args, int index)
{
	pthread_mutex_lock(&args->common_data->print_mutex);
	printf("%d %d is sleeping\n", get_rel_time(args->start_time), index);
	pthread_mutex_unlock(&args->common_data->print_mutex);
	ft_usleep_sleep(args, index);
}

void	think_cycle(t_args *args, int index)
{
	pthread_mutex_lock(&args->common_data->print_mutex);
	printf("%d %d is thinking\n", get_rel_time(args->start_time), index);
	pthread_mutex_unlock(&args->common_data->print_mutex);
	usleep(args->time_sleep * 1000);
}

void	eat_printer(t_args *args, int index)
{
	pthread_mutex_lock(&args->common_data->print_mutex);
	printf("%d %d has taken a fork\n", get_rel_time(args->start_time), index);
	printf("%d %d has taken a fork\n", get_rel_time(args->start_time), index);
	printf("%d %d is eating\n", get_rel_time(args->start_time), index);
	args->last_fed = get_rel_time(args->start_time);
	pthread_mutex_unlock(&args->common_data->print_mutex);
}

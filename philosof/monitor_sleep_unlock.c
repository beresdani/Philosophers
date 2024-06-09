/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_lock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:47:59 by dberes            #+#    #+#             */
/*   Updated: 2024/05/27 11:48:03 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep_eat(t_args *args, int index)
{
	int			last_fed;
	int			time_eat;

	pthread_mutex_lock(&args->mutex);
	last_fed = args->last_fed;
	time_eat = args->time_eat;
	pthread_mutex_unlock(&args->mutex);
	while (get_rel_time(args->start_time) - last_fed < time_eat)
	{
		usleep(200);
		pthread_mutex_lock(&args->common_data->deadphil_mutex);
		if (args->common_data->death == 1)
		{
			pthread_mutex_unlock(&args->common_data->deadphil_mutex);
			return (1);
		}
		pthread_mutex_unlock(&args->common_data->deadphil_mutex);
		if (check_death(args, index))
			return (1);
	}
	return (0);
}

int	ft_usleep_sleep(t_args *args, int index)
{
	int			sleep_start;
	int			time_sleep;

	pthread_mutex_lock(&args->mutex);
	sleep_start = get_rel_time(args->start_time);
	time_sleep = args->time_sleep;
	pthread_mutex_unlock(&args->mutex);
	while (get_rel_time(args->start_time) - sleep_start < time_sleep)
	{
		usleep(200);
		pthread_mutex_lock(&args->common_data->deadphil_mutex);
		if (args->common_data->death == 1)
		{
			pthread_mutex_unlock(&args->common_data->deadphil_mutex);
			return (1);
		}
		pthread_mutex_unlock(&args->common_data->deadphil_mutex);
		if (check_death(args, index))
			return (1);
	}
	return (0);
}

int	monitor_death_end(t_args *args, t_common *common_data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (check_death(&args[i], i + 1) || common_data->ended)
			return (1);
		i++;
		if (i >= common_data->num_phil)
			i = 0;
	}
}

int	philo_putstr(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}

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
	int			dead_philo;

	pthread_mutex_lock(&args->mutex);
	last_fed = args->last_fed;
	time_eat = args->time_eat;
	pthread_mutex_unlock(&args->mutex);
	//printf("index: %d, last fed: %d\n", index, last_fed);
	while (get_rel_time(args->start_time) - last_fed < time_eat)
	{
		pthread_mutex_lock(&args->common_data->deadphil_mutex);
		dead_philo = args->common_data->death;
		pthread_mutex_unlock(&args->common_data->deadphil_mutex);
		usleep(200);
		if (dead_philo == 1 || check_death(args, index))
		{
			//printf("eat check %d\n", index);
			return (1);
		}
	}
	return (0);
}

int	ft_usleep_sleep(t_args *args, int index)
{
	int			sleep_start;
	int			time_sleep;
	int			death_value;

	pthread_mutex_lock(&args->mutex);
	sleep_start = get_rel_time(args->start_time);
	time_sleep = args->time_sleep;
	pthread_mutex_unlock(&args->mutex);
	pthread_mutex_lock(&args->common_data->deadphil_mutex);
	death_value = args->common_data->death;
	pthread_mutex_unlock(&args->common_data->deadphil_mutex);
	while (get_rel_time(args->start_time) - sleep_start < time_sleep)
	{
		usleep(200);
		if (death_value == 1 || check_death(args, index))
			return (1);
	}
	return (0);
}

int	monitor_death_end(t_args *args, t_common *common_data)
{
	int i;

	i = 0;
	while (1)
    {
        //usleep(1000); // Sleep for 1 millisecond to reduce CPU usage
		if (check_death(&args[i], i + 1) || common_data->ended)
		{
			return 1;
		}
		i++;
		if (i >= common_data->num_phil)
		{
			i = 0;
		}
    }
}

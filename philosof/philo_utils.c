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

void	ft_usleep_eat(t_args *args, int index)
{
	long long	start_time;
	int			last_fed;
	int			time_eat;
	int			dead_philo;

	pthread_mutex_lock(&args->mutex);
	start_time = args->start_time;
	last_fed = args->last_fed;
	time_eat = args->time_eat;
	pthread_mutex_unlock(&args->mutex);
	while (get_rel_time(start_time) - last_fed < time_eat)
	{
		pthread_mutex_lock(&args->common_data->deadphil_mutex);
		dead_philo = args->common_data->death;
		pthread_mutex_unlock(&args->common_data->deadphil_mutex);
		usleep(200);
		if (dead_philo == 1 || check_death(args, index))
		{
			//printf("eat check %d\n", index);
			break ;
		}
	}
}

void	ft_usleep_sleep(t_args *args, int index)
{
	long long	start_time;
	int			sleep_start;
	int			time_sleep;
	//int			dead_philo;

	pthread_mutex_lock(&args->mutex);
	start_time = args->start_time;
	sleep_start = get_rel_time(start_time);
	time_sleep = args->time_sleep;
	pthread_mutex_unlock(&args->mutex);
	while (get_rel_time(start_time) - sleep_start < time_sleep)
	{
		/*pthread_mutex_lock(&args->common_data->deadphil_mutex);
		dead_philo = args->common_data->death;
		//printf("dead philo %d\n", dead_philo);
		pthread_mutex_unlock(&args->common_data->deadphil_mutex);*/
		usleep(200);
		if (args->common_data->death == 1 || check_death(args, index))
		{
			//printf("sleep check %d %d\n", index, args->death);
			break ;
		}
	}
}
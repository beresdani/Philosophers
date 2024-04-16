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
	if ((get_timestamp() - args->last_fed) >= args->time_to_die)
	{
		//printf ("%lld\n", get_timestamp() - args->last_fed);
		pthread_mutex_lock(&args->mutex);
		args->death = 1;
		printf("Dead philo: %d\n", args->dead_philo);
		if (args->dead_philo == -1)
			args->dead_philo = index;
		printf("Dead philo index: %d\n", args->dead_philo);
		pthread_mutex_unlock(&args->mutex);
		return (1);
	}
	return (0);	
}

void	sleep_cycle(t_args *args, int index)
{
	pthread_mutex_lock(&args->mutex);
	printf("%lld Phil %d is sleeping\n", get_timestamp(), index);
	pthread_mutex_unlock(&args->mutex);
	usleep(args->time_sleep * 1000);	
}

void	think_cycle(t_args *args, int index)
{
	printf("%lld Phil %d is thinking\n", get_timestamp(), index);
	pthread_mutex_unlock(&args->mutex);
	usleep(args->time_sleep *1000);
}

void	stop_eating(t_args *args, int index)
{
	pthread_mutex_lock(&args->mutex);
	//printf("Phil %d has finished eating\n", index);
	args->fork_array[index - 1] = 0;
	if (index != args->num_phil)
		args->fork_array[index] = 0;
	else
		args->fork_array[0] = 0;
	pthread_mutex_unlock(&args->mutex);
}
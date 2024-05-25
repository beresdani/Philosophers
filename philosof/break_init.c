/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:15:06 by dberes            #+#    #+#             */
/*   Updated: 2024/05/25 13:15:19 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_args *args)
{
	if (pthread_mutex_init(&args->mutex, NULL) != 0)
	{
		printf("Mutex initialization failed.\n");
		return (1);
	}
	return (0);
}

int	mutex_initializer(pthread_mutex_t *fork_array, int num_phil)
{
	int	i;

	i = 0;
	while (i < num_phil)
	{
		if (pthread_mutex_init(&fork_array[i], NULL) != 0)
		{
			printf("Mutex initialization failed.\n");
			destroyer(fork_array, i);
			free_2d_array((void **)fork_array);
			return (1);
		}
		i++;
	}
	return (0);
}

void	break_death(t_args *args, pthread_t *philo)
{
	int	i;
	int	num_phil;

	i = 0;
	pthread_mutex_lock(&args->mutex);
	num_phil = args->num_phil;
	pthread_mutex_unlock(&args->mutex);
	while (i < num_phil)
	{
		//pthread_mutex_unlock(&args->mutex);
		pthread_join(philo[i], NULL);
		//pthread_mutex_lock(&args->mutex);
		i++;
	}
	pthread_mutex_lock(&args->mutex);
	printf("%d %d died\n", get_rel_time(args->common_data->start_time),
		args->common_data->dead_philo);
	pthread_mutex_unlock(&args->mutex);
	pthread_mutex_destroy(&args->mutex);
}

void	break_ended(t_args *args, pthread_t *philo)
{
	int	i;
	int	num_phil;

	i = 0;
	pthread_mutex_lock(&args->mutex);
	num_phil = args->num_phil;
	pthread_mutex_unlock(&args->mutex);
	while (i < num_phil)
	{
		//pthread_mutex_unlock(&args->mutex);
		pthread_join(philo[i], NULL);
		//pthread_mutex_lock(&args->mutex);
		i++;
	}
	//pthread_mutex_unlock(&args->mutex);
	pthread_mutex_destroy(&args->mutex);
}

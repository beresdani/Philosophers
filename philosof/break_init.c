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

void	print_death(t_args *args)
{
	printf("%d %d died\n", get_rel_time(args->common_data->start_time),
		args->common_data->dead_philo);
	args->common_data->death_print = 1;
}

void	break_ended(t_args *args, pthread_t *philo)
{
	int	i;
	int	num_phil;

	i = 0;
	num_phil = args->common_data->num_phil;
	while (i < num_phil)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&args->mutex);
}

void	break_fail(t_args *args, pthread_t *philo, int last)
{
	int	i;

	i = 0;
	while (i < last)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&args->mutex);
}

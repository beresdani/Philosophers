/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:15:25 by dberes            #+#    #+#             */
/*   Updated: 2024/05/25 13:15:29 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_common_data(t_common *common_data,
	pthread_mutex_t *fork_array, int num_phil)
{
	if (common_data == NULL)
	{
		printf("Memory allocation failed.\n");
		free_2d_array((void **)fork_array);
		return (1);
	}
	if (pthread_mutex_init(&common_data->print_mutex, NULL) != 0)
	{
		printf("Mutex initialization failed.\n");
		return (1);
	}
	if (pthread_mutex_init(&common_data->deadphil_mutex, NULL) != 0)
	{
		printf("Mutex initialization failed.\n");
		return (1);
	}
	common_data->num_phil = num_phil;
	common_data->dead_philo = -1;
	common_data->death = 0;
	common_data->death_print = 0;
	common_data->ended = 0;
	common_data->start_time = get_timestamp();
	return (0);
}

int	check_fork_array(pthread_mutex_t *fork_array)
{
	if (fork_array == NULL)
	{
		printf("Memory allocation failed.\n");
		return (1);
	}
	return (0);
}

int	check_join(t_args *args, pthread_t *philo)
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
	return (0);
}

int	check_death(t_args *args, int index)
{
	int	dead_philo;
	int	last_fed;

	pthread_mutex_lock(&args->common_data->deadphil_mutex);
	dead_philo = args->common_data->dead_philo;
	pthread_mutex_unlock(&args->common_data->deadphil_mutex);
	pthread_mutex_lock(&args->mutex);
	last_fed = args->last_fed;
	pthread_mutex_unlock(&args->mutex);
	if ((get_rel_time(args->start_time) - last_fed) >= args->time_to_die)
	{
		pthread_mutex_lock(&args->common_data->deadphil_mutex);
		args->common_data->death = 1;
		pthread_mutex_unlock(&args->common_data->deadphil_mutex);
		pthread_mutex_lock(&args->common_data->deadphil_mutex);
		if (dead_philo == -1)
			args->common_data->dead_philo = index;
		pthread_mutex_unlock(&args->common_data->deadphil_mutex);
		pthread_mutex_lock(&args->common_data->print_mutex);
		if (args->common_data->death_print == 0)
			print_death(args);
		pthread_mutex_unlock(&args->common_data->print_mutex);
		return (1);
	}
	return (0);
}

int	check_end(t_args *args, int num_eats)
{
	int	is_end;
	int	num_rounds;

	pthread_mutex_lock(&args->mutex);
	is_end = args->is_end;
	pthread_mutex_unlock(&args->mutex);
	pthread_mutex_lock(&args->mutex);
	num_rounds = args->num_rounds;
	pthread_mutex_unlock(&args->mutex);
	if (is_end && num_eats == num_rounds - 1)
	{
		pthread_mutex_lock(&args->common_data->print_mutex);
		args->common_data->ended = 1;
		pthread_mutex_unlock(&args->common_data->print_mutex);
		return (1);
	}
	return (0);
}

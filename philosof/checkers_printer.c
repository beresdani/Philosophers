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

int	check_common_data(t_common *common_data, pthread_mutex_t *fork_array)
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
	common_data->dead_philo = -1;
	common_data->death = 0;
	common_data->ended = 0;
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
	int	death;
	int ended;

	pthread_mutex_lock(&args->common_data->deadphil_mutex);
	death = args->common_data->death;
	pthread_mutex_unlock(&args->common_data->deadphil_mutex);
	pthread_mutex_lock(&args->common_data->print_mutex);
	ended = args->common_data->ended;
	pthread_mutex_unlock(&args->common_data->print_mutex);
	//usleep(100);
	if (death)
	{
		break_death(args, philo);
		return (1);
	}
	if (ended)
	{
		break_ended(args, philo);
		return (1);
	}
	return (0);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops_fills.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:46:31 by dberes            #+#    #+#             */
/*   Updated: 2024/05/25 13:46:34 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	looper_args(t_args *args, char **argv, t_common *common_data,
	pthread_mutex_t	*fork_array)
{
	fill_args(args, argv, common_data, fork_array);
	if (init_mutex(args))
		return (1);
	fill_endparams(args, argv);
	return (0);
}

int	looper_threads(t_args *args, pthread_t *philo, int i)
{
	if (fill_times(args, i))
		return (1);
	if (create_threads(args, philo, i))
		return (1);
	return (0);
}

void	fill_endparams(t_args *args, char **argv)
{
	if (argv[5])
	{
		args->is_end = 1;
		args->num_rounds = philo_atoi(argv[5]);
	}
}

void	fill_args(t_args *args, char **argv, t_common *common_data,
	pthread_mutex_t *fork_array)
{
	args->common_data = common_data;
	args->time_to_die = philo_atoi(argv[2]);
	args->time_eat = philo_atoi(argv[3]);
	args->time_sleep = philo_atoi(argv[4]);
	args->num_phil = philo_atoi(argv[1]);
	args->is_end = 0;
	args->fork_array = fork_array;
}

int	fill_times(t_args *args, int i)
{
	args->start_time = args->common_data->start_time;
	args->last_fed = get_rel_time(args->start_time);
	args->phil_index = i + 1;
	return (0);
}

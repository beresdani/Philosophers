/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:45:09 by dberes            #+#    #+#             */
/*   Updated: 2024/04/16 13:45:12 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	int		index;
	t_args	*args;

	args = (t_args *)arg;
	index = args->phil_index;
	if (args->common_data->num_phil % 2 == 0)
	{
		if (index % 2 == 1)
			odd_loop(args, index);
		else
			even_loop(args, index);
	}
	else
	{
		if (index == args->common_data->num_phil)
			last_phil_loop(args, index);
		else if (index % 2 == 1)
			odd_loop(args, index);
		else
			even_loop(args, index);
	}
	//free_index(args);
	return (NULL);
}

int	main(int argc, char **argv)
{
	int				i;
	pthread_t		philo[200];
	t_args			*args;
	t_common		*common_data;
	pthread_mutex_t	*fork_array;

	if (check_input(argc, argv))
		return (1);
	fork_array = create_fork_array(argv);
	common_data = malloc(sizeof(t_common));
	args = malloc(sizeof(t_args) * philo_atoi(argv[1]));
	if (check_mallocs(fork_array, common_data, args, philo_atoi(argv[1])))
		return (1);
	i = 0;
	while (i < philo_atoi(argv[1]))
	{
		if (looper_args(&args[i], argv, common_data, fork_array)
			|| looper_threads(&args[i], philo, i))
			return (1);
		i++;
	}
	monitor_death_end(args, common_data);
	check_join(args, philo);
	return (free_args(args, common_data->num_phil), 0);
}

int	check_mallocs(pthread_mutex_t *fork_array,
	t_common *common_data, t_args *args, int num_phil)
{
	if (fork_array == NULL)
		return (1);
	if (check_common_data(common_data, fork_array, num_phil))
		return (1);
	if (check_args(args, common_data))
		return (1);
	return (0);
}

void	thread_join_loop(t_args *args, pthread_t *philo)
{
	while (1)
	{
		if (check_join(args, philo))
			break ;
	}
}

int	check_args(t_args *args, t_common *common_data)
{
	if (args == NULL)
	{
		//fork array, free everything
		free (common_data);
		return (1);
	}
	return (0);
}

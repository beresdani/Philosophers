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
	index = *args->phil_index;
	if (args->num_phil % 2 == 0)
	{
		if (index % 2 == 1)
			odd_loop(args, index);
		else
			even_loop(args, index);
	}
	else
	{
		if (index == args->num_phil)
			last_phil_loop(args, index);
		else if (index % 2 == 1)
			odd_loop(args, index);
		else
			even_loop(args, index);
	}
	return (NULL);
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

void fill_args(t_args *args, char **argv, t_common *common_data)
{
	args->common_data = common_data;
	args->num_phil = philo_atoi(argv[1]);
	args->time_to_die = philo_atoi(argv[2]);
	args->time_eat = philo_atoi(argv[3]);
	args->time_sleep = philo_atoi(argv[4]);
	args->is_end = 0;
	args->death = 0;
}

int	main(int argc, char **argv)
{
	int				i;
	pthread_t		philo[200];
	t_args			*args;
	t_common		*common_data;
	pthread_mutex_t	*fork_array;

	if (check_input(argc))
		return (1);
	fork_array = (pthread_mutex_t *)malloc(philo_atoi(argv[1])
			* sizeof(pthread_mutex_t));
	if (check_fork_array(fork_array))
		return (1);
	if (mutex_initializer(fork_array, philo_atoi(argv[1])))
		return (1);
	common_data = malloc(sizeof(t_common));
	if (check_common_data(common_data, fork_array))
		return (1);
	common_data->dead_philo = -1;
	i = 0;
	while (i < philo_atoi(argv[1]))
	{
		args = malloc(sizeof(t_args));
		if (check_args(args))
			return (1);
		fill_args(args, argv, common_data);
		args->fork_array = fork_array;
		if (init_mutex(args))
			return (1);
		fill_endparams(args, argv);
		if (fill_times(args, i))
			return (1);
		if (create_threads(args, philo, i))
			return (1);
		i++;
	}
	while (1)
	{
		if (check_join(args, philo))
			break ;
	}
	free_phil_index(args);
	return (0);
}

int	check_input(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Wrong input\n");
		return (1);
	}
	return (0);
}

int	init_mutex(t_args *args)
{
	if (pthread_mutex_init(&args->mutex, NULL) != 0)
	{
		printf("Mutex initialization failed.\n");
		return (1);
	}
	return (0);
}

int	check_common_data(t_common *common_data, pthread_mutex_t *fork_array)
{
	if (common_data == NULL)
	{
		printf("Memory allocation failed.\n");
		free_2d_array((void **)fork_array);
		return (1);
	}
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

int	check_args(t_args *args)
{
	if (args == NULL)
	{
		free_phil_index(args);
		return (1);
	}
	return (0);
}

int	create_threads(t_args *args, pthread_t *philo, int i)
{
	if (pthread_create(&philo[i], NULL, &routine, args) != 0)
	{
		free_phil_index(args);
		printf("Failed to create thread");
		return (1);
	}
	return (0);
}

void	fill_endparams(t_args *args, char **argv)
{
	if (argv[5])
	{
		args->is_end = 1;
		args->ended = 0;
		args->num_rounds = philo_atoi(argv[5]);
	}
}

int	fill_times(t_args *args, int i)
{
	args->start_time = get_timestamp();
	args->last_fed = get_timestamp();
	args->phil_index = malloc(sizeof(int));
	if (args->phil_index == NULL)
		return (1);
	*(args->phil_index) = i + 1;
	return (0);
}

int	check_join(t_args *args, pthread_t *philo)
{
	if (args->death)
	{
		break_death(args, philo);
		return (1);
	}
	if (args->ended)
	{
		break_ended(args, philo);
		return (1);
	}
	return (0);
}

void	break_death(t_args *args, pthread_t *philo)
{
	int i;

	i = 0;
	pthread_mutex_lock(&args->mutex);
	while (i < args->num_phil)
	{
		//pthread_mutex_unlock(&args->mutex);
		pthread_join(philo[i], NULL);
		//pthread_mutex_lock(&args->mutex);
		i++;
	}
	printf("%lld %d died\n", get_timestamp(),
		args->common_data->dead_philo);
	pthread_mutex_unlock(&args->mutex);
	pthread_mutex_destroy(&args->mutex);
}

void	break_ended(t_args *args, pthread_t *philo)
{
	int i;

	i = 0;
	while (i < args->num_phil)
	{
		//pthread_mutex_unlock(&args->mutex);
		pthread_join(philo[i], NULL);
		//pthread_mutex_lock(&args->mutex);
		i++;
	}
	pthread_mutex_destroy(&args->mutex);
}

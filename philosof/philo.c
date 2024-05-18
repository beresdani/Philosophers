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
	if (fork_array == NULL)
		return (1);
	common_data = malloc(sizeof(t_common));
	if (check_common_data(common_data, fork_array))
		return (1);
	i = 0;
	while (i < philo_atoi(argv[1]))
	{
		args = malloc(sizeof(t_args));
		if (looper_args(args, argv, common_data, fork_array)
			|| looper_threads(args, philo, i))
			return (1);
		i++;
	}
	check_join(args, philo);
	return (free_phil_index(args), 0);
}

pthread_mutex_t	*create_fork_array(char **argv)
{
	pthread_mutex_t	*fork_array;
	int num_philos;
	
	num_philos = philo_atoi(argv[1]);
	fork_array = (pthread_mutex_t *)malloc(num_philos
			* sizeof(pthread_mutex_t));
	if (check_fork_array(fork_array)
		|| mutex_initializer(fork_array, num_philos))
		return (NULL);
	return (fork_array);
}

int	check_input(int argc, char **argv)
{
	int i;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong input\n");
		return (1);
	}
	i = 0;
	while (i < argc - 1)
	{
		if (philo_atoi(argv[i + 1]) < 1)
		{
			printf("Wrong input\n");
			return (1);
		}
		i++;
	} 
	return (0);
}

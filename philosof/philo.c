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
	int		loop;

	args = (t_args *)arg;
	index = *args->phil_index;
	loop = 1;
	//printf("fork_array status are the start: \n");
	//print_fork_array(args);
	if (args->num_phil % 2 == 0)
	{
		if (index%2 == 1)
			odd_loop(args, index);
		else
			even_loop(args, index);
	}
	else
	{
		if (index%2 == 1)
			odd_loop(args, index);
		else
			even_loop(args, index);
	}
	return NULL;
}

int	main(int argc, char **argv)
{
	int				i;
	pthread_t   	philo[philo_atoi(argv[1])];
	//pthread_mutex_t	mutex;
	t_args			*args;
	int				*fork_array;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong input\n");
		return (1);
	}
	fork_array = malloc(philo_atoi(argv[1]) * sizeof(int));
	if (fork_array == NULL) 
	{
		printf("Memory allocation failed.\n");
		return 1;
	}
	memset(fork_array, 0, philo_atoi(argv[1]) * sizeof(int));
	i = 0;
	while (i < philo_atoi(argv[1]))
	{
		args = malloc(sizeof(t_args));
		if (args == NULL)
		{
			free(fork_array);
			return (1);
		}
		if (pthread_mutex_init(&args->mutex, NULL) != 0) 
		{
		printf("Mutex initialization failed.\n");
		return 1;
   		}
		args->num_phil = philo_atoi(argv[1]);
		args->fork_array = fork_array;
		args->time_to_die = philo_atoi(argv[2]);
		args->time_eat = philo_atoi(argv[3]);
		args->time_sleep = philo_atoi(argv[4]);
		args->is_end = 0;
		args->death = 0;
		args->dead_philo = -1;
		if (argv[5])
		{
			args->is_end = 1;
			args->ended = 0;
			args->num_rounds = philo_atoi(argv[5]);
		}
		args->start_time = get_timestamp();
		args->last_fed = get_timestamp();
		args->phil_index = malloc(sizeof(int));
		if (args->phil_index == NULL)
			return (1);
		*(args->phil_index) = i + 1;
		if (pthread_create(&philo[i], NULL, &routine, args) != 0)
		{
			free(args->phil_index);
            printf("Failed to create thread");
            return (1);
		}
		i++;
	}
	while (1)
	{
		if (args->death)
		{
			i = 0;
			pthread_mutex_lock(&args->mutex); // Lock the mutex before canceling threads
			while (i < philo_atoi(argv[1]))
			{
				pthread_mutex_unlock(&args->mutex); // Unlock the mutex before canceling the thread
				pthread_join(philo[i], NULL); // Wait for the thread to exit
				pthread_mutex_lock(&args->mutex); // Lock the mutex after joining the thread
				i++;
			}
			printf("%lld Phil %d died\n", get_timestamp(), args->dead_philo);
			pthread_mutex_unlock(&args->mutex); // Unlock the mutex after canceling all threads
			pthread_mutex_destroy(&args->mutex);
			free(args->phil_index);
			break ;
		}
		if (args->ended)
		{
			pthread_mutex_destroy(&args->mutex);
			free(args->phil_index);
			break ;
		}
	}
	free(args);
	return (0);
}

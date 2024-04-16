#include "philo.h"



long long	get_timestamp()
{
	long long		timestamp_1;
	long long		timestamp_2;
	long long		timestamp;

	struct timeval tv;
    gettimeofday(&tv, NULL); // Get current time

	timestamp_1 = tv.tv_usec/1000;
	timestamp_2 = tv.tv_sec*1000;
	timestamp = timestamp_2 + timestamp_1;
	return (timestamp);
}

int	philo_atoi(char	*str)
{
	int	result;
	int	digit;
	int	i;

	i = 0;
	result = 0;
	while(str[i])
	{
		digit = str[i] - 48;
		result = result * 10 + digit;
		i++;
	}
	return (result);
}

void	put_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	check_death(t_args *args)
{
	if ((get_timestamp() - args->last_fed) >= args->time_to_die)
	{
		//printf ("%lld\n", get_timestamp() - args->last_fed);
		pthread_mutex_lock(&args->mutex);
		args->death = 1;
		args->dead_philo = *args->phil_index;
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
	pthread_mutex_lock(&args->mutex);
}

void	think_cycle(t_args *args, int index)
{
	printf("%lld Phil %d is thinking\n", get_timestamp(), index);
	pthread_mutex_unlock(&args->mutex);
	usleep(args->time_sleep *1000);
}

void	stop_eating(t_args *args, int index)
{
	printf("Phil %d has finished eating\n", index);
	args->fork_array[index - 1] = 0;
	if (index != args->num_phil)
		args->fork_array[index] = 0;
	else
		args->fork_array[0] = 0;
	pthread_mutex_unlock(&args->mutex);
}

int	odd_loop(t_args *args, int index)
{
	int fork1;
	int	*is_eating;
	int	num_eats;

	fork1 = 0;
	is_eating = 0;
	while (1)
	{
		if (check_death(args) || args->death)
			return (0);

		//fork 1
		pthread_mutex_lock(&args->mutex);
		if (args->fork_array[index - 1])
			printf("Phil %d Fork taken\n", index);
		else if (!args->fork_array[index - 1])
		{
			args->fork_array[index - 1] = 1;
			fork1 = 1;
			printf("%lld Phil %d has taken a fork\n", get_timestamp(), index);
		}
		pthread_mutex_unlock(&args->mutex);

		//fork 2 + eating
		pthread_mutex_lock(&args->mutex);
		if (index == args->num_phil)
			last_phil_fork2(args, index, &is_eating); 
		else if (fork1 && args->fork_array[index])
			printf("Phil %d Fork taken\n", index);
		else if (fork1 && !args->fork_array[index])
		{
			args->fork_array[index] = 1;
			printf("%lld Phil %d has taken a fork\n", get_timestamp(), index);
			is_eating = 1;
			printf("%lld Phil %d is eating\n", get_timestamp(), index);
			args->last_fed = get_timestamp();
			usleep(args->time_eat * 1000);
		}
		pthread_mutex_unlock(&args->mutex);
		if (check_death(args) || args->death)
			return (0);
		if (args->is_end && num_eats == args->num_rounds - 1)
		{
			args->ended = 1;
			return NULL;
		}

		//finished_eating
		pthread_mutex_lock(&args->mutex);
		if (is_eating == 1)
		{
			is_eating = 0;
			stop_eating(args, index);
		}
		
		//sleeping
		sleep_cycle(args, index);
		if (check_death(args) || args->death)
			return NULL;

		//thinking
		think_cycle(args, index);
		if (check_death(args) || args->death)
			return NULL;
		num_eats++;
	}
}

void	last_phil_fork2(t_args *args, int index, int *is_eating)
{
	if (args->fork_array[0])
		printf("Phil %d Fork taken\n", index);
	else if (!args->fork_array[0])
	{
		args->fork_array[0] = 1;
		printf("%lld Phil %d has taken a fork\n", get_timestamp(), index);
		is_eating = 1;
		printf("%lld Phil %d is eating\n", get_timestamp(), index);
		args->last_fed = get_timestamp();
		usleep(args->time_eat * 1000);
	}
	pthread_mutex_unlock(&args->mutex);
}

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
		if (index == args->num_phil)
			last_philo_loop(args, index);
		else if (index%2 == 1)
			odd_loop(args, index);
		else
			even_loop(args, index);
	}
	return (0);
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
	/*i= 0;
	while (i < philo_atoi(argv[1]))
	{
		printf("%d\n", args->fork_array[i]);
		i++;
	}*/
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
			printf("%lld Phil %d has died\n", get_timestamp(), args->dead_philo);
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

void print_fork_array(t_args *args)
{
	int i;

	i = 0;
	while (i < args->num_phil)
	{
		printf("%d\n", args->fork_array[i]);
		i++;
	}
}

/*
int	main(int argc, char **argv)
{
	int			i;
	pthread_t   philo[philo_atoi(argv[1])];
	t_args		*args_array[philo_atoi(argv[1])];

	if (argc < 5 || argc > 6)
	{
		printf("Wrong input\n");
		return (1);
	}
	
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < philo_atoi(argv[1]))
	{
		args_array[i] = malloc(sizeof(t_args));
		if (args_array[i] == NULL)
			return (1);
		args_array[i]->num_phil = philo_atoi(argv[1]);
		args_array[i]->time_to_die = philo_atoi(argv[2]) * 1000;
		args_array[i]->time_eat = philo_atoi(argv[3]) * 1000;
		args_array[i]->time_sleep = philo_atoi(argv[4]) * 1000;
		args_array[i]->is_end = 0;
		if (argv[5])
		{
			args_array[i]->is_end = 1;
			args_array[i]->num_rounds = philo_atoi(argv[5]);
		}
		args_array[i]->start_time = get_timestamp();
		args_array[i]->phil_index = malloc(sizeof(int));
		if (args_array[i]->phil_index == NULL)
			return (1);
		*(args_array[i]->phil_index) = i + 1;
		if (pthread_create(&philo[i], NULL, &routine, args_array[i]) != 0)
		{
			free(args_array[i]->phil_index);
            free(args_array[i]);
            perror("Failed to create thread");
            return (1);
		}
		i++;
	}
	i = 0;
	while (i < philo_atoi(argv[1]))
	{
		if (pthread_join(philo[i], NULL) != 0)
			return 2;
		free(args_array[i]->phil_index);
        free(args_array[i]); // Free memory after thread completes
		i++;
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}
*/
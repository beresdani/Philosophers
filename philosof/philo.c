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
}

void	think_cycle(t_args *args, int index)
{
	printf("%lld Phil %d is thinking\n", get_timestamp(), index);
	pthread_mutex_unlock(&args->mutex);
	usleep(args->time_sleep *1000);
}

void	stop_eating(t_args *args, int index)
{
	pthread_mutex_lock(&args->mutex);
	printf("Phil %d has finished eating\n", index);
	args->fork_array[index - 1] = 0;
	if (index != args->num_phil)
		args->fork_array[index] = 0;
	else
		args->fork_array[0] = 0;
	pthread_mutex_unlock(&args->mutex);
}

int	try_to_eat(t_args *args, int index)
{
	int	fork1;

	fork1 = 0;
	pthread_mutex_lock(&args->mutex);
	/*if (args->fork_array[index - 1])
		printf("Phil %d Fork taken\n", index);*/
	if (!args->fork_array[index - 1])
	{
		args->fork_array[index - 1] = 1;
		fork1 = 1;
		printf("%lld Phil %d has taken a fork\n", get_timestamp(), index);
	}
	pthread_mutex_unlock(&args->mutex);

	//fork 2 + eating
	pthread_mutex_lock(&args->mutex);
	if (fork1 && index == args->num_phil && !args->fork_array[0])
	{
		args->fork_array[0] = 1;
		printf("%lld Phil %d has taken a fork\n", get_timestamp(), index);
		printf("%lld Phil %d is eating\n", get_timestamp(), index);
		args->last_fed = get_timestamp();
		usleep(args->time_eat * 1000);
		pthread_mutex_unlock(&args->mutex);
		stop_eating(args, index);
		return (1);
	}
	else if (fork1 && !args->fork_array[index])
	{
		args->fork_array[index] = 1;
		printf("%lld Phil %d has taken a fork\n", get_timestamp(), index);
		printf("%lld Phil %d is eating\n", get_timestamp(), index);
		args->last_fed = get_timestamp();
		usleep(args->time_eat * 1000);
		pthread_mutex_unlock(&args->mutex);
		stop_eating(args, index);
		return (1);
	}
	args->fork_array[index - 1] = 0;
	pthread_mutex_unlock(&args->mutex);
	return (0);
}

void	last_phil_fork2(t_args *args, int index)
{
	/*if (args->fork_array[0])
		printf("Phil %d Fork taken\n", index);*/
	if (!args->fork_array[0])
	{
		args->fork_array[0] = 1;
		printf("%lld Phil %d has taken a fork\n", get_timestamp(), index);
		printf("%lld Phil %d is eating\n", get_timestamp(), index);
		args->last_fed = get_timestamp();
		usleep(args->time_eat * 1000);
	}
	//pthread_mutex_unlock(&args->mutex);
}

int	even_loop(t_args *args, int index)
{
	int	num_eats;

	num_eats = 0;
	while (1)
	{
		if (check_death(args) || args->death)
			return (0);

		//thinking
		printf("%lld Phil %d is thinking\n", get_timestamp(), index);
		usleep(args->time_eat * 1000);
		while (1)
		{
			if (check_death(args) || args->death)
				return (0);
			if (try_to_eat(args, index) == 1)
				break ;
		}
		usleep(args->time_eat * 1000);
		if (check_death(args) || args->death)
			return (0);

		//fork 1
		
		if (check_death(args) || args->death)
			return (0);
		if (args->is_end && num_eats == args->num_rounds - 1)
		{
			args->ended = 1;
			return (0);
		}

		//finished_eating
		/*pthread_mutex_lock(&args->mutex);
		if (is_eating == 1)
		{
			is_eating = 0;
			stop_eating(args, index);
		}*/
		
		//sleeping
		sleep_cycle(args, index);
		if (check_death(args) || args->death)
			return (0);
		num_eats++;
	}
}

int	odd_loop(t_args *args, int index)
{
	int	num_eats;

	num_eats = 0;
	while (1)
	{
		while (1)
		{
			if (check_death(args) || args->death)
				return (0);
			if (try_to_eat(args, index) == 1)
				break ;
		}
		if (check_death(args) || args->death)
			return (0);
		if (args->is_end && num_eats == args->num_rounds - 1)
		{
			args->ended = 1;
			return (0);
		}

		//finished_eating
		/*pthread_mutex_lock(&args->mutex);
		if (is_eating == 1)
		{
			is_eating = 0;
			stop_eating(args, index);
		}*/
		
		//sleeping
		sleep_cycle(args, index);
		if (check_death(args) || args->death)
			return (0);
		
		//thinking
		think_cycle(args, index);
		if (check_death(args) || args->death)
			return (0);
		num_eats++;
	}
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
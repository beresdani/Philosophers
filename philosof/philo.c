#include "philo.h"

pthread_mutex_t mutex;

int	get_timestamp()
{
	int	timestamp;

	struct timeval tv;
    gettimeofday(&tv, NULL); // Get current time

    //printf("Seconds since Epoch: %ld\n", tv.tv_sec);
    //printf("Microseconds: %ld\n", tv.tv_usec);
	timestamp = tv.tv_usec/1000;
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

void	*routine(void *arg)
{
	int		index;
	//int		start_eat_time;
	t_args	*args;

	args = (t_args *)arg;
	//start_eat_time = 
	index = *args->phil_index;
	pthread_mutex_lock(&mutex);
	printf("Phil %d is eating\n", index);
	pthread_mutex_unlock(&mutex);

	pthread_mutex_lock(&mutex);
	printf("Phil %d is sleeping\n", index);
	pthread_mutex_unlock(&mutex);

	pthread_mutex_lock(&mutex);
	printf("Phil %d is thinking\n", index);
	pthread_mutex_unlock(&mutex);

	pthread_mutex_lock(&mutex);
	printf("Phil %d has taken a fork\n", index);
	pthread_mutex_unlock(&mutex);

	pthread_mutex_lock(&mutex);
	printf("Phil %d has died\n", index);
	pthread_mutex_unlock(&mutex);
	free(args->phil_index);
	return (0);
}

int	run_threads(t_args *args)
{
	pthread_t   philo[args->num_phil];
    int         i;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < args->num_phil)
	{
		args = (t_args *)malloc(sizeof(t_args));
		if (args == NULL)
			return (1);
		args->phil_index = malloc(sizeof(int));
		if (args->phil_index == NULL)
		{
			free (args);
			return (1);
		}
		*args->phil_index = i + 1;
		//printf("%d\n", *a);
		if (pthread_create(&philo[i], NULL, &routine, args) != 0)
		{
			free (args->phil_index);
			free (args);
			perror("Failed to create thread");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < args->num_phil)
	{
		if (pthread_join(philo[i], NULL) != 0)
			return 2;
		i++;
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}

int	main(int argc, char **argv)
{
	t_args	args;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong input\n");
		return (1);
	}
	args.num_phil = philo_atoi(argv[1]);
	args.time_to_die = philo_atoi(argv[2]);
	args.time_eat = philo_atoi(argv[3]);
	args.time_sleep = philo_atoi(argv[4]);
	args.is_end = 0;
	if (argv[5])
	{
		args.is_end = 1;
		args.num_rounds = philo_atoi(argv[5]);
	}
	args.start_time = get_timestamp();
	run_threads(&args);
	return (0);
}
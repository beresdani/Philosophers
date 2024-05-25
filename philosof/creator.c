#include "philo.h"

pthread_mutex_t	*create_fork_array(char **argv)
{
	pthread_mutex_t	*fork_array;
	int				num_philos;

	num_philos = philo_atoi(argv[1]);
	fork_array = (pthread_mutex_t *)malloc(num_philos
			* sizeof(pthread_mutex_t));
	if (check_fork_array(fork_array)
		|| mutex_initializer(fork_array, num_philos))
		return (NULL);
	return (fork_array);
}

int	create_threads(t_args *args, pthread_t *philo, int i)
{
	if (pthread_create(&philo[i], NULL, &routine, args) != 0)
	{
		free_args(args);
		printf("Failed to create thread");
		return (1);
	}
	return (0);
}

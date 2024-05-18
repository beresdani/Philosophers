#include "philo.h"

int	check_common_data(t_common *common_data, pthread_mutex_t *fork_array)
{
	if (common_data == NULL)
	{
		printf("Memory allocation failed.\n");
		free_2d_array((void **)fork_array);
		return (1);
	}
	common_data->dead_philo = -1;
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

int	check_join(t_args *args, pthread_t *philo)
{
	int	death;
	int ended;

	pthread_mutex_lock(&args->mutex);
	death = args->death;
	pthread_mutex_unlock(&args->mutex);
	pthread_mutex_lock(&args->mutex);
	ended = args->ended;
	pthread_mutex_unlock(&args->mutex);
	usleep(100);
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

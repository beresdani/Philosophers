#include "philo.h"

int	init_mutex(t_args *args)
{
	if (pthread_mutex_init(&args->mutex, NULL) != 0)
	{
		printf("Mutex initialization failed.\n");
		return (1);
	}
	if (pthread_mutex_init(&args->common_data->print_mutex, NULL) != 0)
	{
		printf("Mutex initialization failed.\n");
		return (1);
	}
	if (pthread_mutex_init(&args->common_data->deadphil_mutex, NULL) != 0)
	{
		printf("Mutex initialization failed.\n");
		return (1);
	}
	return (0);
}

void	break_death(t_args *args, pthread_t *philo)
{
	int	i;
	int	num_phil;

	i = 0;
	pthread_mutex_lock(&args->mutex);
	num_phil = args->num_phil;
	pthread_mutex_unlock(&args->mutex);
	while (i < num_phil)
	{
		//pthread_mutex_unlock(&args->mutex);
		pthread_join(philo[i], NULL);
		//pthread_mutex_lock(&args->mutex);
		i++;
	}
	pthread_mutex_lock(&args->mutex);
	printf("%lld %d died\n", get_timestamp(),
		args->common_data->dead_philo);
	pthread_mutex_unlock(&args->mutex);
	pthread_mutex_destroy(&args->mutex);
}

void	break_ended(t_args *args, pthread_t *philo)
{
	int	i;
	int	num_phil;

	i = 0;
	pthread_mutex_lock(&args->mutex);
	num_phil = args->num_phil;
	pthread_mutex_unlock(&args->mutex);
	while (i < num_phil)
	{
		//pthread_mutex_unlock(&args->mutex);
		pthread_join(philo[i], NULL);
		//pthread_mutex_lock(&args->mutex);
		i++;
	}
	//pthread_mutex_unlock(&args->mutex);
	pthread_mutex_destroy(&args->mutex);
}

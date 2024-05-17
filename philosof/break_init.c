#include "philo.h"

int	init_mutex(t_args *args)
{
	if (pthread_mutex_init(&args->mutex, NULL) != 0)
	{
		printf("Mutex initialization failed.\n");
		return (1);
	}
	return (0);
}

void	break_death(t_args *args, pthread_t *philo)
{
	int	i;

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
	int	i;

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

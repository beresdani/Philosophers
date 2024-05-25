#include "philo.h"

int	ft_usleep_eat(t_args *args, int index)
{
	int			last_fed;
	int			time_eat;
	int			dead_philo;

	pthread_mutex_lock(&args->mutex);
	last_fed = args->last_fed;
	time_eat = args->time_eat;
	pthread_mutex_unlock(&args->mutex);
	while (get_rel_time(args->start_time) - last_fed < time_eat)
	{
		pthread_mutex_lock(&args->common_data->deadphil_mutex);
		dead_philo = args->common_data->death;
		pthread_mutex_unlock(&args->common_data->deadphil_mutex);
		usleep(200);
		if (dead_philo == 1 || check_death(args, index))
		{
			//printf("eat check %d\n", index);
			return (1);
		}
	}
	return (0);
}

int	ft_usleep_sleep(t_args *args, int index)
{
	int			sleep_start;
	int			time_sleep;
	int			death_value;

	pthread_mutex_lock(&args->mutex);
	sleep_start = get_rel_time(args->start_time);
	time_sleep = args->time_sleep;
	pthread_mutex_unlock(&args->mutex);
	pthread_mutex_lock(&args->common_data->deadphil_mutex);
	death_value = args->common_data->death;
	pthread_mutex_unlock(&args->common_data->deadphil_mutex);
	while (get_rel_time(args->start_time) - sleep_start < time_sleep)
	{
		/*pthread_mutex_lock(&args->common_data->deadphil_mutex);
		dead_philo = args->common_data->death;
		//printf("dead philo %d\n", dead_philo);
		pthread_mutex_unlock(&args->common_data->deadphil_mutex);*/
		usleep(200);
		if (death_value == 1 || check_death(args, index))
			return (1);
	}
	return (0);
}

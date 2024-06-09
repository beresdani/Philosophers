#include "philo.h"

int	pick_left_fork_even(t_args *args, int index)
{
	pthread_mutex_lock(&args->fork_array[index - 1]);
	pthread_mutex_lock(&args->common_data->deadphil_mutex);
	if (args->common_data->death == 0)
		eat_printer(args, index);
	pthread_mutex_unlock(&args->common_data->deadphil_mutex);
	if (ft_usleep_eat(args, index))
	{
		pthread_mutex_unlock(&args->fork_array[index - 1]);
		pthread_mutex_unlock(&args->fork_array[index % args->num_phil]);
		return (1);
	}
	pthread_mutex_unlock(&args->fork_array[index - 1]);
	pthread_mutex_unlock(&args->fork_array[index % args->num_phil]);
	return (0);
}

int	pick_right_fork_even(t_args *args, int index)
{
	pthread_mutex_lock(&args->fork_array[index % args->num_phil]);
	pthread_mutex_lock(&args->common_data->deadphil_mutex);
	if (args->common_data->death == 1)
	{
		pthread_mutex_unlock(&args->common_data->deadphil_mutex);
		pthread_mutex_unlock(&args->fork_array[index % args->num_phil]);
		return (1);
	}
	pthread_mutex_unlock(&args->common_data->deadphil_mutex);
	if (check_death(args, index))
	{
		pthread_mutex_unlock(&args->fork_array[index % args->num_phil]);
		return (1);
	}
	return (0);
}

int	pick_left_fork_odd(t_args *args, int index)
{
	pthread_mutex_lock(&args->fork_array[index - 1]);
	pthread_mutex_lock(&args->common_data->deadphil_mutex);
	if (args->common_data->death == 1)
	{
		pthread_mutex_unlock(&args->common_data->deadphil_mutex);
		pthread_mutex_unlock(&args->fork_array[index - 1]);
		return (1);
	}
	pthread_mutex_unlock(&args->common_data->deadphil_mutex);
	if (check_death(args, index))
	{
		pthread_mutex_unlock(&args->fork_array[index - 1]);
		return (1);
	}
	return (0);
}

int	pick_right_fork_odd(t_args *args, int index)
{
	pthread_mutex_lock(&args->fork_array[index % args->num_phil]);
	pthread_mutex_lock(&args->common_data->deadphil_mutex);
	if (args->common_data->death == 0)
		eat_printer(args, index);
	pthread_mutex_unlock(&args->common_data->deadphil_mutex);
	if (ft_usleep_eat(args, index))
	{
		pthread_mutex_unlock(&args->fork_array[index % args->num_phil]);
		pthread_mutex_unlock(&args->fork_array[index - 1]);
		return (1);
	}
	pthread_mutex_unlock(&args->fork_array[index % args->num_phil]);
	pthread_mutex_unlock(&args->fork_array[index - 1]);
	return (0);
}

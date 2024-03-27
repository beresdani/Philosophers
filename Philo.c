#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>


pthread_mutex_t mutex;

int	get_timestamp()
{
	struct timeval tv;
    gettimeofday(&tv, NULL); // Get current time

    printf("Seconds since Epoch: %ld\n", tv.tv_sec);
    printf("Microseconds: %ld\n", tv.tv_usec);
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

int		*routine(void *arg)
{
	int	action;

	action = *(int *)arg
	if (action == 1)
	{
		put_str("Philo is eating\n");
		usleep(time_eat/1000);
		return (1);
	}
	else if (activity == 2)
	{
		put_str("Philo is sleeping\n");
		usleep(time_sleep/1000);
		return (2);
	}
	else
		put_str("Philo is thinking\n");

	put_str("Philo has taken a fork\n");

	if ()		
	put_str("Philo has died\n");
}

int	run_threads(int phil_num)
{
	pthread_t   philo[phil_num];
    int         i;
	//int			*fork_array[argv[1]];

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < phil_num)
	{
		if (pthread_create(&philo[i], NULL, &routine, NULL) != 0)
		{
			perror("Failed to create thread");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < phil_num)
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
	int	num;

	num = *argv[1] - 48;
	run_threads(num);
	return (0);
}
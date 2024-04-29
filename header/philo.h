#ifndef PHILO_H
# define PHILO_H

/*********************************
 * 	INCLUDES
 *********************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

/*********************************
 * 	STRUCTS
 *********************************/

typedef struct s_args
{
    pthread_mutex_t	mutex;
	pthread_mutex_t *fork_array;
    int				num_phil;
    long long		time_sleep;
    long long		time_eat;
    long long		time_to_die;
	long long		last_fed;
    int				num_rounds;
    long long		start_time;
    int				is_end;
    int				ended;
    int				*phil_index;
    int				death;
    struct s_common *common_data;
}   t_args;

typedef struct s_common
{
    int				dead_philo;
}   t_common;



/*********************************
 * 	FUNCTION PROTOTYPES
 *********************************/

long long	get_timestamp();
int			philo_atoi(char	*str);
void		put_str(char *str);
void		*routine(void *arg);
int			run_threads(t_args *args);
int			check_death(t_args *args, int index);
void		print_fork_array(t_args *args);
void		sleep_cycle(t_args *args, int index);
void		think_cycle(t_args *args, int index);
int			odd_loop(t_args *args, int index);
int			even_loop(t_args *args, int index);
int			last_phil_loop(t_args *args, int index);
int			try_to_eat(t_args *args, int index);
int			try_to_eat_last(t_args *args, int index);
void		stop_eating(t_args *args, int index);
int			mutex_initializer(pthread_mutex_t *fork_array);
void		free_stuff(t_args *args);
void		destroyer(t_args *args, int i);
void		free_2d_array_i(void ***arr, int i);
void		free_2d_array(void **ptr);


#endif
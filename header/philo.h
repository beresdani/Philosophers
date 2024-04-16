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
    pthread_mutex_t mutex;
    int 		    num_phil;
    long long	    time_sleep;
    long long	    time_eat;
    long long	    time_to_die;
	long long	    last_fed;
    int 		    num_rounds;
    long long	    start_time;
    int 		    is_end;
    int             ended;
    int 		    *phil_index;
    int             death;
    int             dead_philo;
    int             *fork_array;
}   t_args;


/*********************************
 * 	FUNCTION PROTOTYPES
 *********************************/

long long	get_timestamp();
int			philo_atoi(char	*str);
void		put_str(char *str);
void		*routine(void *arg);
int			run_threads(t_args *args);
int         check_death(t_args *args);
void        print_fork_array(t_args *args);
void		sleep_cycle(t_args *args, int index);
void		think_cycle(t_args *args, int index);
void        odd_loop(t_args *args, int index);
void        even_loop(t_args *args, int index);
void        last_phil_fork2(t_args *args, int index, int *is_eating);



#endif
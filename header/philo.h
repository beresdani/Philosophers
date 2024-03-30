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

/*********************************
 * 	STRUCTS
 *********************************/

typedef struct s_args
{
    int num_phil;
    int time_sleep;
    int time_eat;
    int time_to_die;
    int num_rounds;
    int start_time;
    int is_end;
    int *phil_index;
}   t_args;


/*********************************
 * 	FUNCTION PROTOTYPES
 *********************************/

long long	get_timestamp();
int			philo_atoi(char	*str);
void		put_str(char *str);
void		*routine(void *arg);
int			run_threads(t_args *args);


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:28:29 by dberes            #+#    #+#             */
/*   Updated: 2024/05/16 17:28:34 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*********************************
 * 	INCLUDES
 *********************************/

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

/*********************************
 * 	STRUCTS
 *********************************/

typedef struct s_args
{
	pthread_mutex_t	mutex;
	pthread_mutex_t	*fork_array;
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
	struct s_common	*common_data;
}	t_args;

typedef struct s_common
{
	int				dead_philo;
}	t_common;

/*********************************
 * 	FUNCTION PROTOTYPES
 *********************************/

long long			get_timestamp(void);
int					get_rel_time(long long start_time);
int					philo_atoi(char	*str);
void				put_str(char *str);
void				*routine(void *arg);
int					run_threads(t_args *args);
int					check_death(t_args *args, int index);
int					check_end(t_args *args, int num_eats);
int					time_till_death(t_args *args);
void				print_fork_array(t_args *args);
void				sleep_cycle(t_args *args, int index);
void				think_cycle(t_args *args, int index);
int					odd_loop(t_args *args, int index);
int					even_loop(t_args *args, int index);
int					last_phil_loop(t_args *args, int index);
int					try_to_eat(t_args *args, int index);
int					try_to_eat_last(t_args *args, int index);
void				stop_eating(t_args *args, int index);
int					mutex_initializer(pthread_mutex_t *fork_array,
						int num_phil);
void				free_phil_index(t_args *args);
void				destroyer(pthread_mutex_t *fork_array, int i);
void				free_2d_array_i(void ***arr, int i);
void				free_2d_array(void **ptr);
void				fill_args(t_args *args, char **argv, t_common *common_data,
						pthread_mutex_t *fork_array);
void				fill_endparams(t_args *args, char **argv);
int					fill_times(t_args *args, int i);
void				break_death(t_args *args, pthread_t *philo);
void				break_ended(t_args *args, pthread_t *philo);
void				check_join(t_args *args, pthread_t *philo);
int					create_threads(t_args *args, pthread_t *philo, int i);
int					check_args(t_args *args);
int					check_fork_array(pthread_mutex_t *fork_array);
int					check_common_data(t_common *common_data,
						pthread_mutex_t *fork_array);
int					check_input(int argc);
int					init_mutex(t_args *args);
int					looper_args(t_args *args, char **argv,
						t_common *common_data, pthread_mutex_t	*fork_array);
int					looper_threads(t_args *args, pthread_t *philo, int i);
pthread_mutex_t		*create_fork_array(char **argv);
#endif
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
	long long		time_sleep;
	long long		time_eat;
	long long		time_to_die;
	long long		last_fed;
	long long		start_time;
	int				num_rounds;
	int				is_end;
	int				phil_index;
	int				num_phil;
	struct s_common	*common_data;
}	t_args;

typedef struct s_common
{
	int				num_phil;
	int				ended;
	int				death;
	int				death_print;
	int				dead_philo;
	long long		start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	deadphil_mutex;
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
int					sleep_cycle(t_args *args, int index);
int					think_cycle(t_args *args, int index);
int					odd_loop(t_args *args, int index);
int					even_loop(t_args *args, int index);
int					try_to_eat_odd(t_args *args, int index);
int					try_to_eat_even(t_args *args, int index);
void				stop_eating(t_args *args, int index);
int					mutex_initializer(pthread_mutex_t *fork_array,
						int num_phil);
void				free_phil_index(t_args *args);
void				destroyer(pthread_mutex_t *fork_array, int i);
void				free_2d_array_i(void ***arr, int i);
void				free_2d_array(void **ptr);
void				free_args(t_args *args, int last);
void				free_threads(pthread_t *philo, int num_phil);
void				free_index(t_args *args);
void				fill_args(t_args *args, char **argv, t_common *common_data,
						pthread_mutex_t *fork_array);
void				fill_endparams(t_args *args, char **argv);
int					fill_times(t_args *args, int i);
void				print_death(t_args *args);
void				break_ended(t_args *args, pthread_t *philo);
void				break_fail(t_args *args, pthread_t *philo, int last);
int					check_join(t_args *args, pthread_t *philo);
int					create_threads(t_args *args, pthread_t *philo, int i);
int					check_args(t_args *args, t_common *common_data);
int					check_fork_array(pthread_mutex_t *fork_array);
int					check_common_data(t_common *common_data,
						pthread_mutex_t *fork_array, int num_phil);
int					check_input(int argc, char **argv);
int					init_mutex(t_args *args);
int					looper_args(t_args *args, char **argv,
						t_common *common_data, pthread_mutex_t	*fork_array);
int					looper_threads(t_args *args, pthread_t *philo, int i);
pthread_mutex_t		*create_fork_array(char **argv);
int					ft_usleep_eat(t_args *args, int index);
int					ft_usleep_sleep(t_args *args, int index);
void				eat_printer(t_args *args, int index);
void				thread_join_loop(t_args *args, pthread_t *philo);
int					check_mallocs(pthread_mutex_t	*fork_array,
						t_common *common_data, t_args *args, int num_phil);
void				unlocker(t_args *args, int index);
int					monitor_death_end(t_args *args, t_common *common_data);
int					philo_putstr(char *s, int fd);
int					pick_left_fork_even(t_args *args, int index);
int					pick_right_fork_even(t_args *args, int index);
int					pick_left_fork_odd(t_args *args, int index);
int					pick_right_fork_odd(t_args *args, int index);

#endif
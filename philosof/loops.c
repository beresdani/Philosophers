/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:46:07 by dberes            #+#    #+#             */
/*   Updated: 2024/04/16 13:46:27 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	try_to_eat_even(t_args *args, int index)
{
	if (pick_right_fork_even(args, index))
		return (1);
	if (pick_left_fork_even(args, index))
		return (1);
	return (0);
}

int	try_to_eat_odd(t_args *args, int index)
{
	if (pick_left_fork_odd(args, index))
		return (1);
	if (pick_right_fork_odd(args, index))
		return (1);
	return (0);
}

int	even_loop(t_args *args, int index)
{
	int	num_eats;

	num_eats = 0;
	while (1)
	{
		if (try_to_eat_even(args, index))
			return (1);
		if (check_end(args, num_eats))
			return (1);
		pthread_mutex_lock(&args->common_data->deadphil_mutex);
		if (args->common_data->death)
		{
			pthread_mutex_unlock(&args->common_data->deadphil_mutex);
			return (1);
		}
		pthread_mutex_unlock(&args->common_data->deadphil_mutex);
		if (sleep_cycle(args, index))
			return (1);
		if (think_cycle(args, index))
			return (1);
		num_eats++;
	}
}

int	odd_loop(t_args *args, int index)
{
	int	num_eats;

	num_eats = 0;
	while (1)
	{
		if (try_to_eat_odd(args, index))
			return (1);
		if (check_end(args, num_eats))
			return (1);
		pthread_mutex_lock(&args->common_data->deadphil_mutex);
		if (args->common_data->death)
		{
			pthread_mutex_unlock(&args->common_data->deadphil_mutex);
			return (1);
		}
		pthread_mutex_unlock(&args->common_data->deadphil_mutex);
		if (sleep_cycle(args, index))
			return (1);
		if (think_cycle(args, index))
			return (1);
		num_eats++;
	}
}

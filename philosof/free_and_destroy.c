/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:32:09 by dberes            #+#    #+#             */
/*   Updated: 2024/04/29 14:32:13 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_2d_array(void **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
		{
			if (ptr[i])
				free(ptr[i]);
			i++;
		}
		free(ptr);
	}
}

/*
void	free_index(t_args *args)
{
	if (args->phil_index != NULL)
	{
		free(args->phil_index);
		args->phil_index = NULL;
	}
}*/

void	destroyer(pthread_mutex_t *fork_array, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&fork_array[j]);
		j++;
	}
}

void	free_args(t_args *args, int last)
{
	int	i;

	i = 0;
	if (args == NULL)
		return ;
	if (args->fork_array != NULL)
	{
		while (i < last)
		{
			pthread_mutex_destroy(&args->fork_array[i]);
			i++;
		}
		free(args->fork_array);
	}
	if (args->common_data != NULL)
	{
		pthread_mutex_destroy(&args->common_data->print_mutex);
		pthread_mutex_destroy(&args->common_data->deadphil_mutex);
		pthread_mutex_destroy(&args->mutex);
		free(args->common_data);
	}
	free(args);
}

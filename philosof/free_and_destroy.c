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

void	free_2d_array_i(void ***arr, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free((*arr)[j++]);
	free(*arr);
	*arr = NULL;
}

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

void	free_phil_index(t_args *args)
{
	free(args->phil_index);
}

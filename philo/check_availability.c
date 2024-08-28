/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_availability.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosokin <sosokin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 21:56:40 by sosokin           #+#    #+#             */
/*   Updated: 2024/08/22 22:03:09 by sosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_allowed(int *arr, int len, int init_val)
{
	int	is_even;
	int	i;

	is_even = init_val % 2;
	i = 0;
	while (i < len)
	{
		if ((i + 1) % 2 == is_even)
			arr[i] = i + 1;
		i++;
	}
}

void	exclude_from_allowed(t_data *data)
{
	pthread_mutex_lock(data->allowed_mut);
	data->allowed[data->index] = 0;
	if (sum(data->allowed, data->count) == 0)
		set_allowed(data->allowed, data->count, data->index);
	pthread_mutex_unlock(data->allowed_mut);
}

void	check_availability(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(data->allowed_mut);
		if (sum(data->allowed, data->count) == 0)
			set_allowed(data->allowed, data->count, data->index + 1);
		if (data->allowed[data->index])
		{
			if (!(data->count % 2 == 1 && data->index + 1 == data->count
					&& data->allowed[0]))
			{
				pthread_mutex_unlock(data->allowed_mut);
				break ;
			}
		}
		pthread_mutex_unlock(data->allowed_mut);
		usleep(500);
		continue ;
	}
}

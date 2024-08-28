/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosokin <sosokin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:44:09 by sosokin           #+#    #+#             */
/*   Updated: 2024/08/26 21:24:23 by sosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_alive(t_data *data)
{
	pthread_mutex_lock(data->is_dead_mut);
	if (data->is_dead[0])
	{
		pthread_mutex_unlock(data->is_dead_mut);
		return (0);
	}
	pthread_mutex_unlock(data->is_dead_mut);
	return (1);
}

static int	do_cycle(t_data *data, int *eat_counter)
{
	if (!is_alive(data))
		return (0);
	printf("%lu %d is thinking\n", get_time_delta(data->cycle->start_time),
		data->index + 1);
	check_availability(data);
	if (!is_alive(data))
		return (0);
	pthread_mutex_lock(data->forks[data->index]);
	printf("%lu %d has taken a fork\n", get_time_delta(data->cycle->start_time),
		data->index + 1);
	pthread_mutex_lock(data->forks[right(data->index, data->count)]);
	printf("%lu %d has taken a fork\n", get_time_delta(data->cycle->start_time),
		data->index + 1);
	if (!is_alive(data))
		return (0);
	do_work(data->cycle, data->index, data, "eis eating");
	(*eat_counter)++;
	exclude_from_allowed(data);
	pthread_mutex_unlock(data->forks[data->index]);
	pthread_mutex_unlock(data->forks[right(data->index, data->count)]);
	if (!is_alive(data))
		return (0);
	do_work(data->cycle, data->index, data, "sis sleeping");
	return (1);
}

void	*philo(void *arg)
{
	t_data	*data;
	int		eat_counter;
	int		(*cond)(int, int);

	data = (t_data *)arg;
	eat_counter = 0;
	if (data->cycle->eat_count > 0)
		cond = &less;
	else
		cond = &greater;
	while (cond(eat_counter, data->cycle->eat_count))
	{
		if (!do_cycle(data, &eat_counter))
			break ;
	}
	pthread_mutex_lock(data->done_mut);
	data->is_done = 1;
	pthread_mutex_unlock(data->done_mut);
	return (arg);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosokin <sosokin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:05:51 by sosokin           #+#    #+#             */
/*   Updated: 2024/08/29 12:40:08 by sosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_done(t_data **data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_lock(data[i]->done_mut);
		if (!(data[i]->is_done))
		{
			pthread_mutex_unlock(data[i]->done_mut);
			return (0);
		}
		pthread_mutex_unlock(data[i]->done_mut);
		i++;
	}
	return (1);
}

static int	is_dead(int is_died, t_data *data, int i)
{
	if (is_died)
	{
		pthread_mutex_lock(data->is_dead_mut);
		data->is_dead[0] = 1;
		pthread_mutex_unlock(data->is_dead_mut);
		printf("%lu %d died\n", get_time_delta(data->cycle->start_time), i + 1);
		return (1);
	}
	return (0);
}

static void	check_death(t_data **data, int count, t_cycle *cycle)
{
	int	i;
	int	is_died;

	i = 0;
	while (!all_done(data, count))
	{
		pthread_mutex_lock(data[i]->done_mut);
		if (data[i]->is_done)
		{
			pthread_mutex_unlock(data[i]->done_mut);
			continue ;
		}
		pthread_mutex_unlock(data[i]->done_mut);
		pthread_mutex_lock(data[i]->let_mut);
		is_died = (get_time() - (data[i]->last_eat_time)) >= cycle->die_time;
		pthread_mutex_unlock(data[i]->let_mut);
		if (is_dead(is_died, data[i], i))
			return ;
		i++;
		if (i == count)
		{
			i = 0;
			usleep(9000);
		}
	}
}

static int	run_threads(int amount, pthread_t **philos, t_data **data)
{
	int	i;
	int	res;

	i = 0;
	while (i < amount)
	{
		res = pthread_create(philos[i], NULL, &philo, data[i]);
		if (res)
		{
			return (res);
		}
		res = pthread_detach(*(philos[i]));
		if (res)
		{
			return (res);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t	**philos;
	t_data		**data;
	int			phil_numb;
	t_cycle		*cycle;
	int			*num_args;

	if (argc < 5)
		return (printf("At least 4 arguments required!\n"));
	num_args = try_get_args(argv + 1, argc - 1);
	if (!num_args)
		return (1);
	phil_numb = num_args[0];
	philos = create_philos(phil_numb);
	init_all_data(&data, argc, &cycle, num_args);
	if (!cycle || !data)
		free_main_data(philos, data);
	if (run_threads(phil_numb, philos, data))
	{
		free_main_data(philos, data);
		return (1);
	}
	check_death(data, phil_numb, cycle);
	free_main_data(philos, data);
	return (0);
}

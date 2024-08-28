/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosokin <sosokin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:00:14 by sosokin           #+#    #+#             */
/*   Updated: 2024/08/22 21:16:48 by sosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_fields(t_data *data)
{
	data->forks = NULL;
	data->cycle = NULL;
	data->index = 0;
}

static t_data	**init_data_set(int count)
{
	int		i;
	t_data	**data_set;
	t_data	*data;

	i = 0;
	data_set = (t_data **)malloc(sizeof(t_data *) * (count + 1));
	if (!data_set)
		return (NULL);
	while (i < count)
	{
		data_set[i] = NULL;
		data = (t_data *)malloc(sizeof(t_data));
		if (!data)
		{
			free_data_set(data_set);
			return (NULL);
		}
		init_fields(data);
		data_set[i] = data;
		i++;
	}
	data_set[i] = NULL;
	return (data_set);
}

static void	set_fields(t_data **data_set, t_data *sample, t_cycle *cycle,
		pthread_mutex_t ***muts)
{
	pthread_mutex_t	**let_mut;
	pthread_mutex_t	**done_mut;
	int				i;

	let_mut = muts[0];
	done_mut = muts[1];
	i = 0;
	while (data_set[i])
	{
		data_set[i]->forks = sample->forks;
		data_set[i]->cycle = cycle;
		data_set[i]->index = i;
		data_set[i]->last_eat_time = cycle->start_time;
		data_set[i]->let_mut = let_mut[i];
		data_set[i]->done_mut = done_mut[i];
		data_set[i]->is_done = 0;
		data_set[i]->allowed = sample->allowed;
		data_set[i]->count = sample->count;
		data_set[i]->allowed_mut = sample->allowed_mut;
		data_set[i]->is_dead = sample->is_dead;
		data_set[i]->is_dead_mut = sample->is_dead_mut;
		i++;
	}
}

t_data	*get_sample(int forks_numb)
{
	t_data	*sample;

	sample = (t_data *)malloc(sizeof(t_data));
	if (!sample)
		return (NULL);
	sample->count = forks_numb;
	sample->forks = create_mut_arr(forks_numb);
	if (!sample->forks)
		return (free_res(sample, NULL, NULL));
	sample->allowed = (int *)malloc(sizeof(int) * forks_numb);
	if (!sample->allowed)
		return (free_res(sample, NULL, NULL));
	memset(sample->allowed, 0, sizeof(int) * forks_numb);
	sample->allowed_mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(sample->allowed_mut, NULL);
	sample->is_dead = (int *)malloc(sizeof (int));
	sample->is_dead[0] = 0;
	sample->is_dead_mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(sample->is_dead_mut, NULL);
	return (sample);
}

t_data	**init_data(int forks_numb, t_cycle *cycle)
{
	t_data			**data_set;
	t_data			*sample;
	pthread_mutex_t	**muts[2];

	sample = get_sample(forks_numb);
	if (!sample)
		return (NULL);
	muts[0] = create_mut_arr(forks_numb);
	if (!muts[0])
		return (free_res(sample, NULL, NULL));
	muts[1] = create_mut_arr(forks_numb);
	if (!muts[1])
		return (free_res(sample, muts[0], muts[1]));
	data_set = init_data_set(forks_numb);
	if (!data_set)
		return (free_res(sample, muts[0], muts[1]));
	set_fields(data_set, sample, cycle, muts);
	free(sample);
	free(muts[0]);
	free(muts[1]);
	return (data_set);
}

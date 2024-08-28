/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosokin <sosokin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:25:54 by sosokin           #+#    #+#             */
/*   Updated: 2024/08/28 19:34:42 by sosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_t	**create_philos(int amount)
{
	int			i;
	pthread_t	*new;
	pthread_t	**philos;

	philos = (pthread_t **)malloc(sizeof(pthread_t *) * (amount + 1));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < amount)
	{
		new = (pthread_t *)malloc(sizeof(pthread_t));
		if (!new)
		{
			free_arr((void **)philos, &free);
			return (NULL);
		}
		philos[i] = new;
		i++;
	}
	philos[i] = NULL;
	return (philos);
}

pthread_mutex_t	**create_mut_arr(int amount)
{
	int				i;
	pthread_mutex_t	*new;
	pthread_mutex_t	**forks;

	forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * (amount
				+ 1));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < amount)
	{
		new = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!new)
		{
			free_arr((void **)forks, &free);
			return (NULL);
		}
		pthread_mutex_init(new, NULL);
		forks[i] = new;
		i++;
	}
	forks[i] = NULL;
	return (forks);
}

static t_cycle	*set_cycle(int *args, int argc)
{
	t_cycle			*cycle;
	struct timeval	tp;
	struct timezone	tzp;

	cycle = (t_cycle *)malloc(sizeof(t_cycle));
	if (!cycle)
		return (NULL);
	gettimeofday(&tp, &tzp);
	cycle->start_time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	cycle->die_time = args[1];
	cycle->eat_time = args[2];
	cycle->sleep_time = args[3];
	if (argc == 6)
		cycle->eat_count = args[4];
	else
		cycle->eat_count = -1;
	return (cycle);
}

int	init_all_data(t_data ***data, int argc, t_cycle **cycle, int *args)
{
	*cycle = set_cycle(args, argc);
	if (!cycle)
	{
		return (1);
	}
	*data = init_data(args[0], *cycle);
	if (!data)
	{
		return (1);
	}
	return (0);
}

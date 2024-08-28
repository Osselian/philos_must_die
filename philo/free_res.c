/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_res.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosokin <sosokin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:43:17 by sosokin           #+#    #+#             */
/*   Updated: 2024/08/22 21:34:04 by sosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_res(t_data *sample, pthread_mutex_t **let_mut,
		pthread_mutex_t **done_mut)
{
	free_data(sample, 0);
	if (done_mut)
		free_arr((void *)(done_mut), &free);
	if (let_mut)
		free_arr((void *)(let_mut), &free);
	return (NULL);
}

void	*free_arr(void **arr, void (*del)(void *))
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (del)
			(*del)(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

void	free_data(void *data, int is_iter)
{
	t_data	*tmp;

	tmp = (t_data *)data;
	if (tmp->let_mut)
		free(tmp->let_mut);
	if (tmp->done_mut)
		free(tmp->done_mut);
	if (!is_iter)
	{
		if (tmp->is_dead)
			free(tmp->is_dead);
		if (tmp->is_dead_mut)
			free(tmp->is_dead_mut);
		if (tmp->allowed)
			free(tmp->allowed);
		if (tmp->allowed_mut)
			free(tmp->allowed_mut);
		if (tmp->forks)
			free_arr((void **)(tmp->forks), &free);
		if (tmp->cycle)
			free(tmp->cycle);
	}
	free(tmp);
}

void	free_data_set(t_data **data)
{
	int		i;

	if (data)
	{
		i = 0;
		while (data[i])
		{
			free_data(data[i], i);
			i++;
		}
		free(data);
	}
}

void	free_main_data(pthread_t **philos, t_data **data)
{
	if (philos)
		free_arr((void **)philos, &free);
	free_data_set(data);
}

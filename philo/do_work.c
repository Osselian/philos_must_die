/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_work.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosokin <sosokin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:05:53 by sosokin           #+#    #+#             */
/*   Updated: 2024/08/22 20:03:58 by sosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	do_sleep(unsigned long sleep_time)
{
	unsigned long	cur_time;

	cur_time = get_time();
	while ((get_time() - cur_time) < sleep_time)
		usleep(500);
}

void	do_work(t_cycle *cycle, int index, t_data *data, char *mes)
{
	int				time;
	unsigned long	cur_time;
	int				delta;

	printf("%lu %d %s\n", get_time_delta(cycle->start_time), index + 1, mes
		+ 1);
	if (*mes == 'e')
		time = cycle->eat_time;
	else
	{
		cur_time = get_time();
		delta = cur_time - (data->last_eat_time);
		time = cycle->sleep_time - delta;
	}
	do_sleep(time);
	if (*mes == 'e')
	{
		pthread_mutex_lock(data->let_mut);
		data->last_eat_time = get_time();
		pthread_mutex_unlock(data->let_mut);
	}
}

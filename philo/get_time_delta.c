/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_delta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosokin <sosokin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:49:46 by sosokin           #+#    #+#             */
/*   Updated: 2024/08/22 21:34:56 by sosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time_delta(unsigned long start_time)
{
	struct timeval	tp;
	struct timezone	tzp;
	unsigned long	cur_time;

	gettimeofday(&tp, &tzp);
	cur_time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (cur_time - start_time);
}

unsigned long	get_time(void)
{
	struct timeval	tp;
	struct timezone	tzp;
	unsigned long	cur_time;

	gettimeofday(&tp, &tzp);
	cur_time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (cur_time);
}

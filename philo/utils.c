/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosokin <sosokin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:27:24 by sosokin           #+#    #+#             */
/*   Updated: 2024/08/22 22:01:54 by sosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	left(int n, int count)
{
	return ((n - 1 + count) % count);
}

int	right(int n, int count)
{
	return ((n + 1) % count);
}

int	greater(int a, int b)
{
	return (a > b);
}

int	less(int a, int b)
{
	return (a < b);
}

int	sum(int *arr, int len)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (i < len)
		res += arr[i++];
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_converter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosokin <sosokin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 20:48:44 by sosokin           #+#    #+#             */
/*   Updated: 2024/08/28 19:23:24osokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	is_num(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	char	neg;
	int		res;

	neg = 1;
	res = 0;
	while (*str)
	{
		if (*str == ' ' || (*str >= 9 && *str <= 13))
			str++;
		else
			break ;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (ft_isdigit((int)*str))
	{
		res = (res * 10) + *str - '0';
		str++;
	}
	return (res * neg);
}

int	*try_get_args(char **args, int argc)
{
	int	*num_args;
	int	cur;
	int i;

	num_args = (int *)malloc(sizeof(int) * argc);
	if (!num_args)
		return NULL;
	i = 0;
	while (i < argc)
	{
		cur = ft_atoi(*args);
		if (cur < 0 || !is_num(*args))
		{
			printf("Incorrect argument - %s\n", *args);
			free(num_args);
			return (NULL);
		}
		num_args[i] = cur;
		args++;
		i++;
	}
	return (num_args);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosokin <sosokin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:28:00 by sosokin           #+#    #+#             */
/*   Updated: 2024/08/28 19:35:12 by sosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

typedef struct s_cycle
{
	unsigned long	die_time;
	int				eat_time;
	int				sleep_time;
	int				think_time;
	int				eat_count;
	unsigned long	start_time;
}					t_cycle;

typedef struct s_data
{
	pthread_mutex_t	**forks;
	t_cycle			*cycle;
	unsigned long	last_eat_time;
	pthread_mutex_t	*let_mut;
	pthread_mutex_t	*done_mut;
	int				is_done;
	int				*allowed;
	pthread_mutex_t	*allowed_mut;
	int				count;
	int				index;
	int				*is_dead;
	pthread_mutex_t	*is_dead_mut;
}					t_data;

//init.c
pthread_t		**create_philos(int amount);
pthread_mutex_t	**create_mut_arr(int amount);
t_data			**init_data(int forks_numb, t_cycle *cycle);
void			set_priorities(unsigned long *priorities, int len,
					unsigned long value);
int				init_all_data(t_data ***data, int argc, t_cycle **cycle,
					int *args);

//utils.c
int				left(int n, int count);
int				right(int n, int count);
int				less(int a, int b);
int				greater(int a, int b);
int				sum(int *arr, int len);

//philo.c		
void			*philo(void *arg);

//free_res.c
void			*free_arr(void **arr, void (*del)(void *));
void			free_data(void *data, int is_iter);
void			*free_res(t_data *sample, pthread_mutex_t **let_mut,
					pthread_mutex_t **done_mut);
void			free_data_set(t_data **data);
void			free_main_data(pthread_t **philos, t_data **data);

//args_converter.c
int				*try_get_args(char **args, int argc);
int				ft_atoi(const char *str);

//get_time_delta.c
unsigned long	get_time_delta(unsigned long start_time);
unsigned long	get_time(void);

//do_work.c
void			do_work(t_cycle *cycle, int index, t_data *data, char *mes);

//check_availability.c
void			check_availability(t_data *data);
void			exclude_from_allowed(t_data *data);

#endif

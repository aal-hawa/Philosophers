/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:09:24 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/10 19:46:24 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_mutex
{
	pthread_mutex_t printf_mutex;
	pthread_mutex_t noname_mutex;
	pthread_mutex_t timer_mutex;
	pthread_mutex_t last_philo_mutex;
	pthread_mutex_t died_mutex;
	
} t_mutex;

typedef struct s_fork
{
	int	is_allowed; //use mutex
	int index;
} t_fork;

typedef struct s_forks
{
	t_fork *fork;
} t_forks;

typedef struct s_philo
{
	int index;
	int	is_eat_sleep;
	int	is_eat;
	int timer;
	int die_timer;
	
} t_philo;

typedef struct s_philos
{
	t_philo *philo;
	int	last_philo_got_it; //use mutex
} t_philos;

typedef struct s_info
{
	int	philo_count;
	int	to_eat;
	int	to_think;
	int to_sleep;
	int timer_unsleep;  //use mutex
	int is_died; //use mutex
} t_info;

typedef struct s_parm
{
	t_info *info;
	t_forks *forks;
	t_mutex *mutex;
	t_philos *philos;
} t_parm;

int		parsing(t_info *info);
int		init_threads(t_parm *parm);
void	ft_putstr_fd(char *s, int fd, int is_malloc);
int		threads(t_parm *parm);
int		time_now(t_parm *parm);
#endif
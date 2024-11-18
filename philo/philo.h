/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:09:24 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/18 18:47:36 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_mutex
{
	pthread_mutex_t printf_mutex;
	pthread_mutex_t timer_mutex;
	pthread_mutex_t last_philo_mutex;
	pthread_mutex_t died_mutex;
	
} t_mutex;

typedef struct s_fork
{
	pthread_mutex_t fork_mutex;
	int	is_allowed; //use mutex
	int index;
	struct s_fork	*next_fork;
} t_fork;

typedef struct s_philo
{
	int index;
	int	is_eat_sleep;
	int	is_eat;
	int timer;
	int die_timer;
	struct s_philo	*next;
} t_philo;

typedef struct s_info
{
	int	philo_count;
	int	to_eat;
	int	to_think;
	int	to_die;
	int to_sleep;
	int	how_many_eat;
	// unsigned long timer_unsleep;  //use mutex
	int is_died; //use mutex
	int	last_philo_got_it; //use mutex
	int	is_get_timer;
	struct timeval fst_time;

} t_info;

typedef struct s_parm
{
	t_info *info;
	t_fork *fork;
	t_mutex *mutex;
	t_philo *philo;
	pthread_t *pthrd;
} t_parm;

int		parsing(int ac, char **arg);
int		init_threads(t_parm *parm);
void	ft_putstr_fd(char *s, int philo_nbr, int is_malloc, int timer);
int		threads(t_parm *parm);
int		time_now(t_parm *parm);
void	printing(pthread_mutex_t mutex, char *s, int philo_nbr, int timer);
int		check_is_char(char *str);
int		ft_atoi(const char *str);
int		error_massege(char *str, int is_error);
int		init_philo(t_parm *parm);
int		get_cur_time_millscd(t_info *info);
void 	*do_threed_philo(void *ptr);
void	philo_is_die(t_parm *parm, t_philo *philo, int this_time);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:09:24 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/21 17:32:03 by aal-hawa         ###   ########.fr       */
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
	pthread_mutex_t printf_mutex; // destroy
	pthread_mutex_t timer_mutex; // destroy
	pthread_mutex_t last_philo_mutex; // destroy
	pthread_mutex_t died_mutex; // destroy
	int	printf_mutex_check;
	int	timer_mutex_check;
	int	last_philo_mutex_check;
	int	died_mutex_check;
} t_mutex;

typedef struct s_fork // free
{
	pthread_mutex_t fork_mutex; // destroy
	pthread_mutex_t last_eating_mutex; // destroy
	int	is_allowed; //use mutex
	int	last_who_eating; //use mutex
	int index;
	struct s_fork	*next;
} t_fork;

typedef struct s_philo // free
{
	int index;
	int	is_eat_sleep;
	int	is_eat;
	int timer;
	int curr_die_timer;
	int	next_die_timer;
	int how_many_eat;
	t_fork *fork_right; /////////// // free
	t_fork *fork_left;  ////////// // free
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
void	printing(t_parm *parm, char *s, int philo_nbr, int timer);
void	printing_died(t_parm *parm, char *s, int philo_nbr, int timer);
int		check_is_char(char *str);
int		ft_atoi(const char *str);
int		error_massege(char *str, int is_error);
int		init_philo(t_parm *parm);
int		get_cur_time_millscd(t_info *info);
void 	*do_threed_philo(void *ptr);
void	philo_is_die(t_parm *parm, t_philo *philo, int this_time);
void	free_all_mlc(t_parm *parm, int is_error);
#endif
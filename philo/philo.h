/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:09:24 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/27 19:23:03 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_mutex
{
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	timer_mutex;
	pthread_mutex_t	last_philo_mutex;
	pthread_mutex_t	died_mutex;
	int				printf_mutex_check;
	int				timer_mutex_check;
	int				last_philo_mutex_check;
	int				died_mutex_check;
}					t_mutex;

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	last_eating_mutex;
	int				is_allowed;
	int				last_who_eating;
	int				index;
	struct s_fork	*next;
}					t_fork;

typedef struct s_philo
{
	int				index;
	int				is_eat_sleep;
	int				is_eat;
	int				timer;
	int				curr_die_timer;
	int				next_die_timer;
	int				how_many_eat;
	int				is_get_fork_one;
	int				this_time;
	t_fork			*fork_right;
	t_fork			*fork_left;
	struct s_philo	*next;
}					t_philo;

typedef struct s_info
{
	int				philo_count;
	int				to_eat;
	int				to_think;
	int				to_die;
	int				to_sleep;
	int				how_many_eat;
	int				is_died;
	int				last_philo_got_it;
	int				is_get_timer;
	struct timeval	fst_time;
	struct timeval	cur_time;


}					t_info;

typedef struct s_parm
{
	t_info			*info;
	t_fork			*fork;
	t_mutex			*mutex;
	t_philo			*philo;
	pthread_t		*pthrd;
}					t_parm;

int					parsing(int ac, char **arg);
int					init_threads(t_parm *parm);
int					threads(t_parm *parm);
void				printing(t_parm *parm, char *s, int philo_nbr, int timer);
void				printing_died(t_parm *parm, char *s, int philo_nbr,
						int timer);
int					check_is_char(char *str);
int					ft_atoi(const char *str);
int					error_massege(char *str, int is_error);
int					init_philo(t_parm *parm);
int					get_cur_time_millscd(t_info *info);
void				get_first_time_millscd(t_info *info);
void				*do_threed_philo(void *ptr);
void				philo_is_die(t_parm *parm, t_philo **philo);
void				free_all_mlc(t_parm *parm, int is_error);
t_fork				*check_index_fork(t_parm *parm, t_fork *next_fork,
						t_fork *this_fork, int i);
t_philo				*check_index_philo(t_parm *parm, t_philo *next_ph,
						t_philo *this_philo, int i);
void				select_philo_fork(t_parm *parm, t_philo **philo,
						t_info *info);
void				eating_sleeping_thinking(t_parm *parm, t_philo **philo,
						t_info *info);

#endif
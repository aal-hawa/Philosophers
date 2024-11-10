/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:09:24 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/10 13:23:56 by aal-hawa         ###   ########.fr       */
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
	
} t_mutex;

typedef struct s_mutexs
{
	t_mutex *mutex;
} t_mutexs;

typedef struct s_fork
{
	
} t_fork;

typedef struct s_forks
{
	t_fork *fork;
} t_forks;

typedef struct s_info
{
	int	philo_count;
} t_info;

typedef struct s_parm
{
	t_info *info;
	t_forks *forks;
	t_mutexs *mutexs;
} t_parm;

int		parsing(t_info *info);
int		init_threads(t_parm *parm);
void	ft_putstr_fd(char *s, int fd, int is_malloc);
int		threads(t_parm *parm);
int		time_now(t_info *info);
#endif
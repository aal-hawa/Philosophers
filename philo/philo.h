/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:09:24 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/07 13:49:56 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


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
	
} t_info;

typedef struct s_parm
{
	t_info *info;
	t_forks *forks;
	t_mutexs *mutexs;
} t_parm;

int		parsing(t_info *info);
void	init_threads(t_info *info);
void	ft_putstr_fd(char *s, int fd, int is_malloc);
int		threads(t_info *info);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:52:09 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/14 18:43:23 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../philo.h"


int init_fork(t_fork *fork, int index)
{
	int	is_error;
	
	is_error =  pthread_mutex_init(&fork->fork_mutex, NULL);
	if (is_error != 0)
		return (1);
	fork->index = index;
	fork->is_allowed = 1;
	fork->next_fork =  NULL;
}

int init_forks(t_parm *parm)
{
	int	i;
	int	is_error;
	t_fork *this_fork;
	t_fork *next_fork;
	
	next_fork = NULL;
	i = 0;
	while (i < parm->info->philo_count)
	{
		this_fork = malloc(sizeof(t_fork));
		if (!this_fork)
			return (1);
		is_error = init_fork(this_fork, i);
		if (is_error != 0)
			return (1);
		next_fork = this_fork;
		next_fork = next_fork->next_fork;
		i++;
	}
}


int	init_mutex(t_mutex *mutex)
{
	int	is_error;
	
	is_error =  pthread_mutex_init(&mutex->died_mutex, NULL);
	if (is_error != 0)
		return (1);
	is_error =  pthread_mutex_init(&mutex->last_philo_mutex, NULL);
	if (is_error != 0)
		return (1);
	is_error =  pthread_mutex_init(&mutex->printf_mutex, NULL);
	if (is_error != 0)
		return (1);
	is_error =  pthread_mutex_init(&mutex->timer_mutex, NULL);
	if (is_error != 0)
		return (1);
	return (0);
}


int	init_threads(t_parm *parm)
{
	int	is_error;

	is_error = init_forks(parm->info);
	if (!is_error == 1)
		return (-1);
	is_error = init_mutex(parm->mutex);
	if (is_error == 1)
		return (-1);
	return (0);
}

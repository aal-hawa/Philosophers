/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:52:09 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/21 13:38:51 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int init_fork(t_fork *fork, int index)
{
	int	is_error;
	
	is_error =  pthread_mutex_init(&fork->fork_mutex, NULL);
	if (is_error != 0)
		return (-3);
	is_error =  pthread_mutex_init(&fork->last_eating_mutex, NULL);
	if (is_error != 0)
		return (-3);
	fork->index = index;
	fork->is_allowed = 1;
	fork->last_who_eating = -1;
	fork->next =  NULL;
	return (0);
}

int init_forks(t_parm *parm)
{
	int	i;
	int	is_error;
	t_fork *this_fork;
	t_fork *next_fork;
	
	this_fork = NULL;
	next_fork = NULL;
	i = 0;
	while (i < parm->info->philo_count)
	{
		this_fork = malloc(sizeof(t_fork));
		if (!this_fork)
			return (-2);
		is_error = init_fork(this_fork, i);
		if (is_error != 0)
			return (-3);
		if (i == 0)
		{
			parm->fork = this_fork;
			next_fork = this_fork;
		}
		else
		{
			next_fork->next = this_fork;
			next_fork = next_fork->next;
		}
		i++;
	}
	return (0);
}

int	init_mutex(t_mutex *mutex)
{
	int	is_error;
	mutex->died_mutex_check = 0;
	mutex->last_philo_mutex_check = 0;
	mutex->printf_mutex_check = 0;
	mutex->timer_mutex_check = 0;
	

	is_error =  pthread_mutex_init(&mutex->died_mutex, NULL);
	if (is_error != 0)
		return (-4);
	mutex->died_mutex_check = 1;
	is_error =  pthread_mutex_init(&mutex->last_philo_mutex, NULL);
	if (is_error != 0)
		return (-4);
	mutex->last_philo_mutex_check = 1;
	is_error =  pthread_mutex_init(&mutex->printf_mutex, NULL);
	if (is_error != 0)
		return (-4);
	mutex->printf_mutex_check = 1;
	is_error =  pthread_mutex_init(&mutex->timer_mutex, NULL);
	if (is_error != 0)
		return (-4);
	mutex->timer_mutex_check = 1;
	return (0);
}

int	init_philo(t_parm *parm)
{
	int i;
	t_philo	*this_philo;
	t_philo	*first_philo;
	t_philo	*next_ph;
	
	i = 0;
	while (i < parm->info->philo_count)
	{
		this_philo = malloc(sizeof(t_philo));
		if (!this_philo)
			return (-1);
		this_philo->index = i + 1;
		this_philo->is_eat = 0;
		this_philo->is_eat_sleep = 0;
		this_philo->timer = 0;
		this_philo->curr_die_timer = 0;
		this_philo->next_die_timer = 0;
		this_philo->how_many_eat = 0;
		if (i == 0)
		{
			first_philo = this_philo;
			next_ph = this_philo;
		}
		else 
		{
			next_ph->next = this_philo;
			next_ph = next_ph->next;
		}
		i++;
	}
	parm->philo = first_philo;
	next_ph = parm->philo;
	while (next_ph)
		next_ph = next_ph->next;
	return (0);
}

int	init_threads(t_parm *parm)
{
	int	is_error;
	t_mutex	mutex;
	
	parm->mutex = &mutex;
	is_error = init_forks(parm);
	if (is_error != 0)
		return (is_error);
	is_error = init_mutex(parm->mutex);
	if (is_error != 0)
		return (is_error);
	return (0);
}

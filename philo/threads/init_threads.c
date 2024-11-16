/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:52:09 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/16 16:48:06 by aal-hawa         ###   ########.fr       */
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
	parm->fork = this_fork;
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
	return (0);
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

int	init_philo(t_parm *parm)
{
	int i;
	t_philo	*this_philo;
	t_philo	*first_philo;
	t_philo	*next_philo;
	
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
		this_philo->die_timer = 0;
		this_philo->next_philo = NULL;
		if (i == 0)
			first_philo = this_philo;
		next_philo = this_philo;
		next_philo = next_philo->next_philo;
		i++;
	}
	parm->philo = first_philo;
	return (0);
}

int	init_threads(t_parm *parm)
{
	int	is_error;

	is_error = init_forks(parm);
	if (is_error == 1)
		return (-1);
	is_error = init_mutex(parm->mutex);
	if (is_error == 1)
		return (-1);
	return (0);
}
